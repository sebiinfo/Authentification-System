// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "camera.h"
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
#    include "ui_camera_mobile.h"
#else
#    include "ui_camera.h"
#endif

#include "imagesettings.h"
#include "metadatadialog.h"
#include "videosettings.h"
#include <iostream>
#include <string>
#include <QAction>
#include <QActionGroup>
#include <QAudioDevice>
#include <QAudioInput>
#include <QCameraDevice>
#include <QDir>
#include <QImage>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMediaDevices>
#include <QMediaFormat>
#include <QMediaMetaData>
#include <QMediaRecorder>
#include <QMessageBox>
#include <QPalette>
#include <QTimer>
#include <QVideoWidget>

Camera::Camera() : ui(new Ui::Camera)
{
    ui->setupUi(this);
    m_audioInput.reset(new QAudioInput);
    m_captureSession.setAudioInput(m_audioInput.get());

    // Camera devices:

    videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    updateCameras();
    connect(&m_devices, &QMediaDevices::videoInputsChanged, this, &Camera::updateCameras);

    connect(videoDevicesGroup, &QActionGroup::triggered, this, &Camera::updateCameraDevice);

    setCamera(QMediaDevices::defaultVideoInput());
    ui->stacked->setCurrentIndex(0);
}

void Camera::setCamera(const QCameraDevice &cameraDevice)
{
    m_camera.reset(new QCamera(cameraDevice));
    m_captureSession.setCamera(m_camera.data());

    connect(m_camera.data(), &QCamera::activeChanged, this, &Camera::updateCameraActive);
    connect(m_camera.data(), &QCamera::errorOccurred, this, &Camera::displayCameraError);

    if (!m_mediaRecorder) {
        m_mediaRecorder.reset(new QMediaRecorder);
        m_captureSession.setRecorder(m_mediaRecorder.data());
        connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this,
                &Camera::updateRecordTime);
        connect(m_mediaRecorder.data(), &QMediaRecorder::errorChanged, this,
                &Camera::displayRecorderError);
    }

    if (!m_imageCapture) {
        m_imageCapture.reset(new QImageCapture);
        m_captureSession.setImageCapture(m_imageCapture.get());
        connect(m_imageCapture.get(), &QImageCapture::readyForCaptureChanged, this,
                &Camera::readyForCapture);
        connect(m_imageCapture.get(), &QImageCapture::imageCaptured, this,
                &Camera::processCapturedImage);
        connect(m_imageCapture.get(), &QImageCapture::imageSaved, this, &Camera::imageSaved);
        connect(m_imageCapture.get(), &QImageCapture::errorOccurred, this,
                &Camera::displayCaptureError);
    }

    m_captureSession.setVideoOutput(ui->viewfinder);

    updateCameraActive(m_camera->isActive());
    readyForCapture(m_imageCapture->isReadyForCapture());

    if (m_camera->cameraFormat().isNull()) {
        auto formats = cameraDevice.videoFormats();
        if (!formats.isEmpty()) {
            // Choose a decent camera format: Maximum resolution of at least 30 FPS
            QCameraFormat bestFormat;
            for (const auto &fmt : formats) {
                if (bestFormat.maxFrameRate() < 29
                    && fmt.maxFrameRate() > bestFormat.maxFrameRate())
                    bestFormat = fmt;
                else if (bestFormat.maxFrameRate() == fmt.maxFrameRate()
                         && bestFormat.resolution().width() * bestFormat.resolution().height()
                                 < fmt.resolution().width() * fmt.resolution().height())
                    bestFormat = fmt;
            }

            m_camera->setCameraFormat(bestFormat);
            m_mediaRecorder->setVideoFrameRate(bestFormat.maxFrameRate());
        }
    }

    m_camera->start();
}

void Camera::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (m_doImageCapture) {
            takeImage();
        } else {
            if (m_mediaRecorder->recorderState() == QMediaRecorder::RecordingState)
                stop();
            else
                record();
        }
        event->accept();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void Camera::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration() / 1000);
    ui->statusbar->showMessage(str);
}

void Camera::processCapturedImage(int requestId, const QImage &img)
{
    Q_UNUSED(requestId);
    QImage scaledImage =
            img.scaled(ui->viewfinder->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    displayCapturedImage();
    QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}

void Camera::configureCaptureSettings()
{
    if (m_doImageCapture)
        configureImageSettings();
    else
        configureVideoSettings();
}

void Camera::configureVideoSettings()
{
    VideoSettings settingsDialog(m_mediaRecorder.data());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    if (settingsDialog.exec())
        settingsDialog.applySettings();
}

void Camera::configureImageSettings()
{
    ImageSettings settingsDialog(m_imageCapture.get());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);

    if (settingsDialog.exec()) {
        settingsDialog.applyImageSettings();
    }
}

void Camera::record()
{
    m_mediaRecorder->record();
    updateRecordTime();
}

void Camera::pause()
{
    m_mediaRecorder->pause();
}

void Camera::stop()
{
    m_mediaRecorder->stop();
}

void Camera::setMuted(bool muted)
{
    m_captureSession.audioInput()->setMuted(muted);
}

void Camera::takeImage()
{
    m_isCapturingImage = true;
    m_imageCapture->captureToFile();
}

void Camera::displayCaptureError(int id, const QImageCapture::Error error,
                                 const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void Camera::startCamera()
{
    m_camera->start();
}

void Camera::stopCamera()
{
    m_camera->stop();
}

void Camera::updateCameraActive(bool active)
{
    if (active) {
        ui->actionStartCamera->setEnabled(false);
        ui->actionStopCamera->setEnabled(true);
        ui->actionSettings->setEnabled(true);
    } else {
        ui->actionStartCamera->setEnabled(true);
        ui->actionStopCamera->setEnabled(false);
        ui->actionSettings->setEnabled(false);
    }
}

void Camera::setExposureCompensation(int index)
{
    m_camera->setExposureCompensation(index * 0.5);
}

void Camera::displayRecorderError()
{
    if (m_mediaRecorder->error() != QMediaRecorder::NoError)
        QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void Camera::displayCameraError()
{
    if (m_camera->error() != QCamera::NoError)
        QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void Camera::updateCameraDevice(QAction *action)
{
    setCamera(qvariant_cast<QCameraDevice>(action->data()));
}

void Camera::displayViewfinder()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Camera::displayCapturedImage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Camera::readyForCapture(bool ready)
{
    ui->takeImageButton->setEnabled(ready);
}

void Camera::imageSaved(int id, const QString &fileName)
{
    Q_UNUSED(id);
    ui->statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));

    m_isCapturingImage = false;
    if (m_applicationExiting)
        close();
}

void Camera::closeEvent(QCloseEvent *event)
{
    if (m_isCapturingImage) {
        setEnabled(false);
        m_applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}

void Camera::updateCameras()
{
    ui->menuDevices->clear();
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras) {
        QAction *videoDeviceAction = new QAction(cameraDevice.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);

        ui->menuDevices->addAction(videoDeviceAction);
    }
}

void Camera::showMetaDataDialog()
{
    if (!m_metaDataDialog)
        m_metaDataDialog = new MetaDataDialog(this);
    m_metaDataDialog->setAttribute(Qt::WA_DeleteOnClose, false);
    if (m_metaDataDialog->exec() == QDialog::Accepted)
        saveMetaData();
}

void Camera::saveMetaData()
{
    QMediaMetaData data;
    for (int i = 0; i < QMediaMetaData::NumMetaData; i++) {
        QString val = m_metaDataDialog->m_metaDataFields[i]->text();
        if (!val.isEmpty()) {
            auto key = static_cast<QMediaMetaData::Key>(i);
            if (i == QMediaMetaData::CoverArtImage) {
                QImage coverArt(val);
                data.insert(key, coverArt);
            } else if (i == QMediaMetaData::ThumbnailImage) {
                QImage thumbnail(val);
                data.insert(key, thumbnail);
            } else if (i == QMediaMetaData::Date) {
                QDateTime date = QDateTime::fromString(val);
                data.insert(key, date);
            } else {
                data.insert(key, val);
            }
        }
    }
    m_mediaRecorder->setMetaData(data);
}

void Camera::on_register_2_clicked()
{
    ui->stacked->setCurrentIndex(1);
}


void Camera::on_face_recognition_clicked()
{
    ui->stacked->setCurrentIndex(4);
}


void Camera::on_password_clicked()
{
    ui->stacked->setCurrentIndex(2);
}


void Camera::on_back_clicked()
{
    ui->stacked->setCurrentIndex(0);
}


void Camera::on_back_2_clicked()
{
    ui->stacked->setCurrentIndex(0);
}


void Camera::on_back_3_clicked()
{
    ui->stacked->setCurrentIndex(0);
}

void Camera::on_login_2_clicked()
{
    std::string username = ui -> username_input -> text().toStdString();
    std::string password = ui -> password_input -> text().toStdString();
    std::cout <<username<<std::endl;
    std::cout <<password<<std::endl;
    QMessageBox::about(this, "Login Error", "Your username and password do not match.");
    ui->stacked->setCurrentIndex(5);

}


void Camera::on_create_2_clicked()
{
    std::string name = ui -> name -> text().toStdString();
    std::string last_name = ui -> last_name -> text().toStdString();
    std::string user = ui -> username -> text().toStdString();
    std::string pass = ui -> password_2 -> text().toStdString();
    std::string conf_pass = ui -> confirm_password -> text().toStdString();

    std::cout <<name<<std::endl;
    std::cout <<last_name<<std::endl;
    std::cout <<user<<std::endl;
    std::cout <<pass<<std::endl;
    std::cout <<conf_pass<<std::endl;
}


void Camera::on_new_password_clicked()
{
    std::string old = ui -> old_password -> text().toStdString();
    std::string new_pass = ui -> new_pass -> text().toStdString();
    std::string confirmation = ui -> confirm_new -> text().toStdString();

    std::cout <<old<<std::endl;
    std::cout <<new_pass<<std::endl;
    std::cout <<confirmation<<std::endl;
}


void Camera::on_update_password_clicked()
{
    ui->stacked->setCurrentIndex(5);
}


void Camera::on_change_email_clicked()
{
    std::string old_email = ui -> old_email -> text().toStdString();
    std::string new_email = ui -> new_email -> text().toStdString();
    std::string confirm_email = ui -> confirm_email -> text().toStdString();

    std::cout <<old_email<<std::endl;
    std::cout <<new_email<<std::endl;
    std::cout <<confirm_email<<std::endl;
}


void Camera::on_update_email_clicked()
{
    ui->stacked->setCurrentIndex(6);
}


void Camera::on_back_7_clicked()
{
    ui->stacked->setCurrentIndex(5);
}


void Camera::on_back_8_clicked()
{
    ui->stacked->setCurrentIndex(5);
}


void Camera::on_localization_1_clicked()
{
    QMessageBox::about(this, "Localization 1 Authentication", "You have been recognized with a 93.5% accuracy.");
}

void Camera::on_localization_2_clicked()
{
    QMessageBox::about(this, "Localization 2 Authentication", "You have been recognized with a 76.4% accuracy.");
}


void Camera::on_vectorization_1_clicked()
{
    QMessageBox::about(this, "Vectorization 1 Authentication", "You have been recognized with a 85.1% accuracy.");
}



void Camera::on_vectorization_2_clicked()
{
    QMessageBox::about(this, "Vectorization 2 Authentication", "You have been recognized with a 94.7% accuracy.");
}


void Camera::on_classification_1_clicked()
{
    QMessageBox::about(this, "Vectorization 2 Authentication", "You have been recognized with a 83.9% accuracy.");
}


void Camera::on_classification_2_clicked()
{
    QMessageBox::about(this, "Vectorization 2 Authentication", "You have been recognized with a 76.2% accuracy.");
}


void Camera::on_create_account_clicked()
{
    ui->stacked->setCurrentIndex(1);
}


void Camera::on_back_9_clicked()
{
    ui->stacked->setCurrentIndex(5);
}



void Camera::on_forgot_credentials_clicked()
{
    ui->stacked->setCurrentIndex(3);
}


void Camera::on_back_4_clicked()
{
    ui->stacked->setCurrentIndex(2);
}


void Camera::on_get_code_clicked()
{
    std::string change_credentials = ui -> email_code -> text().toStdString();

    std::cout <<change_credentials<<std::endl;
}


void Camera::on_takeImageButton_clicked()
{
    QMessageBox::about(this, "Verification Result", "Using verification methods x, y, and Vectorization 1, your authentication accuracy was __%");
    ui->stacked->setCurrentIndex(5);
}


void Camera::on_photo_library_clicked()
{
    ui->stacked->setCurrentIndex(4);
}

