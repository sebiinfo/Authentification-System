// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "camera.h"
#include <opencv2/imgcodecs.hpp>
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
#include "ui_camera_mobile.h"
#else
#include "ui_camera.h"
#endif
#include "../Model/model.hpp"
#include "config.h"
#include "imagesettings.h"
#include <QAction>
#include <QActionGroup>
#include <QAudioDevice>
#include <QAudioInput>
#include <QCameraDevice>
#include <QDir>
#include <QGraphicsAnchor>
#include <QGraphicsAnchorLayout>
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
#include <QtWidgets>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

// #define PATH_TO_RESOURCES "./"

Camera::Camera() : ui(new Ui::Camera) {
    ui->setupUi(this);

    // Camera devices:

    videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    updateCameras();
    connect(&m_devices, &QMediaDevices::videoInputsChanged, this,
            &Camera::updateCameras);

    connect(videoDevicesGroup, &QActionGroup::triggered, this,
            &Camera::updateCameraDevice);

    setCamera(QMediaDevices::defaultVideoInput());
    ui->stacked->setCurrentIndex(0);
    ui->localization_1->setChecked(true);
    ui->vectorization->setChecked(true);
    ui->classification_1->setChecked(true);
}

void Camera::setCamera(const QCameraDevice &cameraDevice) {
    m_camera.reset(new QCamera(cameraDevice));
    m_captureSession.setCamera(m_camera.data());

    connect(m_camera.data(), &QCamera::activeChanged, this,
            &Camera::updateCameraActive);
    connect(m_camera.data(), &QCamera::errorOccurred, this,
            &Camera::displayCameraError);

    if (!m_imageCapture) {
        m_imageCapture.reset(new QImageCapture);
        m_captureSession.setImageCapture(m_imageCapture.get());
        connect(m_imageCapture.get(), &QImageCapture::readyForCaptureChanged,
                this, &Camera::readyForCapture);
        connect(m_imageCapture.get(), &QImageCapture::imageCaptured, this,
                &Camera::processCapturedImage);
        connect(m_imageCapture.get(), &QImageCapture::imageSaved, this,
                &Camera::imageSaved);
        connect(m_imageCapture.get(), &QImageCapture::errorOccurred, this,
                &Camera::displayCaptureError);
    }

    m_captureSession.setVideoOutput(ui->viewfinder);

    updateCameraActive(m_camera->isActive());
    readyForCapture(m_imageCapture->isReadyForCapture());

    if (m_camera->cameraFormat().isNull()) {
        auto formats = cameraDevice.videoFormats();
        if (!formats.isEmpty()) {
            // Choose a decent camera format: Maximum resolution of at least 30
            // FPS
            QCameraFormat bestFormat;
            for (const auto &fmt : formats) {
                if (bestFormat.maxFrameRate() < 29 &&
                    fmt.maxFrameRate() > bestFormat.maxFrameRate())
                    bestFormat = fmt;
                else if (bestFormat.maxFrameRate() == fmt.maxFrameRate() &&
                         bestFormat.resolution().width() *
                                 bestFormat.resolution().height() <
                             fmt.resolution().width() *
                                 fmt.resolution().height())
                    bestFormat = fmt;
            }

            m_camera->setCameraFormat(bestFormat);
            // m_mediaRecorder->setVideoFrameRate(bestFormat.maxFrameRate());
        }
    }

    m_camera->start();
}

void Camera::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        return;

    switch (event->key()) {
    case Qt::Key_CameraFocus:
        displayViewfinder();
        event->accept();
        break;
    case Qt::Key_Camera:
        if (m_doImageCapture) {
            takeImage("AHHHH");
        }
        event->accept();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void Camera::processCapturedImage(int requestId, const QImage &img) {
    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(ui->viewfinder->size(), Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
    //    displayCapturedImage();
    //    QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}

void Camera::configureCaptureSettings() {
    if (m_doImageCapture)
        configureImageSettings();
}

void Camera::configureImageSettings() {
    ImageSettings settingsDialog(m_imageCapture.get());
    settingsDialog.setWindowFlags(settingsDialog.windowFlags() &
                                  ~Qt::WindowContextHelpButtonHint);

    if (settingsDialog.exec()) {
        settingsDialog.applyImageSettings();
    }
}

void Camera::takeImage(std::string button_clicked) {
    std::string path = "/resources/";
    std::string extension = ".jpg";
    std::string bar = "/";
    std::string aux;
    if (button_clicked == "account_photos") {
        path = path + currentIndex;
        path = path + bar;
        path = path + std::to_string(num_pics);
        path = path + extension;

        std::cout << button_clicked << " path-> " << path << std::endl;
        std::cout << PATH_TO_RESOURCES;
        path = std::string(PATH_TO_RESOURCES) + path;
    } else {
        path = "/resources/temp.jpg";
        path = std::string(PATH_TO_RESOURCES) + path;
    }
    m_isCapturingImage = true;
    m_imageCapture->captureToFile(QString::fromStdString(path));
}

void Camera::displayCaptureError(int id, const QImageCapture::Error error,
                                 const QString &errorString) {
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    m_isCapturingImage = false;
}

void Camera::startCamera() { m_camera->start(); }

void Camera::stopCamera() { m_camera->stop(); }

void Camera::updateCameraActive(bool active) {
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

void Camera::setExposureCompensation(int index) {
    m_camera->setExposureCompensation(index * 0.5);
}

void Camera::displayCameraError() {
    if (m_camera->error() != QCamera::NoError)
        QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void Camera::updateCameraDevice(QAction *action) {
    setCamera(qvariant_cast<QCameraDevice>(action->data()));
}

void Camera::displayViewfinder() { ui->stacked->setCurrentIndex(0); }

// void Camera::displayCapturedImage() { ui->stacked->setCurrentIndex(1); }

void Camera::readyForCapture(bool ready) {
    ui->takeImageButton->setEnabled(ready);
}

void Camera::imageSaved(int id, const QString &fileName) {
    Q_UNUSED(id);
    ui->statusbar->showMessage(
        tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));

    m_isCapturingImage = false;
    if (m_applicationExiting)
        close();
}

void Camera::closeEvent(QCloseEvent *event) {
    if (m_isCapturingImage) {
        setEnabled(false);
        m_applicationExiting = true;
        event->ignore();
    } else {
        event->accept();
    }
}

void Camera::updateCameras() {
    ui->menuDevices->clear();
    const QList<QCameraDevice> availableCameras = QMediaDevices::videoInputs();
    for (const QCameraDevice &cameraDevice : availableCameras) {
        QAction *videoDeviceAction =
            new QAction(cameraDevice.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraDevice));
        if (cameraDevice == QMediaDevices::defaultVideoInput())
            videoDeviceAction->setChecked(true);

        ui->menuDevices->addAction(videoDeviceAction);
    }
}

void Camera::on_register_2_clicked() { ui->stacked->setCurrentIndex(1); }

void Camera::on_face_recognition_clicked() {
    ui->camera->setCurrentIndex(0);
    ui->stacked->setCurrentIndex(4);
    ui->logout->setCurrentIndex(0);
    currentIndex = "";
}

void Camera::on_password_clicked() { ui->stacked->setCurrentIndex(2); }

void Camera::on_back_clicked() { ui->stacked->setCurrentIndex(0); }

void Camera::on_back_2_clicked() { ui->stacked->setCurrentIndex(0); }

void Camera::on_back_3_clicked() { ui->stacked->setCurrentIndex(0); }

void Camera::on_login_2_clicked() {
    std::string username = ui->username_input->text().toStdString();
    std::string password = ui->password_input->text().toStdString();
    bool check = database.checkPasswordandUsername(username, password);
    if (check == true) {
        ui->stacked->setCurrentIndex(5);
    } else {
        QMessageBox::about(this, "Login Error",
                           "Your username and password do not match.");
    }
    ui->username_input->clear();
    ui->password_input->clear();
}

void Camera::on_create_2_clicked() {
    std::string name = ui->name->text().toStdString();
    std::string last_name = ui->last_name->text().toStdString();
    std::string user = ui->username->text().toStdString();
    std::string email = ui->email->text().toStdString();
    std::string pass = ui->password_2->text().toStdString();
    std::string conf_pass = ui->confirm_password->text().toStdString();

    Database::Possible_Errors check =
        database.writeDataToFile(user, name, last_name, pass, conf_pass, email);
    if (name.empty()) {
        QMessageBox::about(this, "Error Creating Account",
                           "There has been an error, you must fill out all "
                           "fields in order to create an account.");
    } else if (user.empty()) {
        QMessageBox::about(this, "Error Creating Account",
                           "There has been an error, you must fill out all "
                           "fields in order to create an account.");
    } else if (last_name.empty()) {
        QMessageBox::about(this, "Error Creating Account",
                           "There has been an error, you must fill out all "
                           "fields in order to create an account.");
    } else if (pass.empty()) {
        QMessageBox::about(this, "Error Creating Account",
                           "There has been an error, you must fill out all "
                           "fields in order to create an account.");
    } else if (conf_pass.empty()) {
        QMessageBox::about(this, "Error Creating Account",
                           "There has been an error, you must fill out all "
                           "fields in order to create an account.");
    } else if (email.empty()) {
        QMessageBox::about(this, "Error Creating Account",
                           "There has been an error, you must fill out all "
                           "fields in order to create an account.");
    } else {
        if (check == 0) {
            currentIndex = database.readRecordFromFile(user)[0];
            std::cout << "This is the new id:" << currentIndex << std::endl;
            ui->camera->setCurrentIndex(1);
            ui->stacked->setCurrentIndex(4);
            ui->logout->setCurrentIndex(0);
            QMessageBox::about(
                this, "Identification Photos",
                "Now you must take 10 pictures with different "
                "facial expressions in order to be able to use the "
                "facial recognition system to log in.");
            ui->name->clear();
            ui->last_name->clear();
            ui->username->clear();
            ui->email->clear();
            ui->password_2->clear();
            ui->confirm_password->clear();
        } else if (check == 1) {
            QMessageBox::about(this, "Error Creating Account",
                               "There has been an error, your confirmed "
                               "password does not match "
                               "your password. Please input the right password "
                               "and try again.");
        } else if (check == 2) {
            QMessageBox::about(
                this, "Error Creating Account",
                "There has been an error, the email you have selected has "
                "already "
                "been taken. Please choose another and try again.");
        } else if (check == 3) {
            QMessageBox::about(
                this, "Error Creating Account",
                "There has been an error, the username you have selected has "
                "already been taken. Please choose another and try again.");
        } else if (check == 4) {
            QMessageBox::about(
                this, "Error Creating Account",
                "There has been an error, the password you chose is not strong "
                "enough. Take a look at the requirements below and try again.");
        }
    }
}

void Camera::on_new_password_clicked() {
    std::string old = ui->old_password->text().toStdString();
    std::string new_pass = ui->new_pass->text().toStdString();
    std::string confirmation = ui->confirm_new->text().toStdString();
    std::string username = ui->username_2->text().toStdString();
    bool check =
        database.change_password(username, old, new_pass, confirmation);
    if (check == true) {
        ui->stacked->setCurrentIndex(5);
        ui->old_password->clear();
        ui->new_pass->clear();
        ui->confirm_new->clear();
        ui->username_2->clear();
    } else {
        QMessageBox::about(
            this, "Error Changing Password",
            "There has been an error when changing password, make sure your "
            "information is valid and try again.");
    }
}

void Camera::on_update_password_clicked() { ui->stacked->setCurrentIndex(6); }

void Camera::on_change_email_clicked() {
    std::string username = ui->usern->text().toStdString();
    std::string password = ui->passw->text().toStdString();
    std::string new_email = ui->confirm_email->text().toStdString();
    bool check = database.change_email(username, password, new_email);
    if (check == true) {
        ui->stacked->setCurrentIndex(5);
        ui->usern->clear();
        ui->passw->clear();
        ui->confirm_email->clear();
    } else {
        QMessageBox::about(
            this, "Error",
            "There has been an error, check your information and try again.");
    }
}

void Camera::on_delete_account_5_clicked() {
    std::string username = ui->username_5->text().toStdString();
    std::string password = ui->password_5->text().toStdString();
    bool check = database.delete_user(username, password);
    if (check == true) {
        ui->stacked->setCurrentIndex(0);
        ui->username_5->clear();
        ui->password_5->clear();
    } else {
        QMessageBox::about(
            this, "Error",
            "There has been an error, check your information and try again.");
    }
}

void Camera::on_update_email_clicked() { ui->stacked->setCurrentIndex(7); }

void Camera::on_back_7_clicked() { ui->stacked->setCurrentIndex(5); }

void Camera::on_back_8_clicked() { ui->stacked->setCurrentIndex(5); }

std::string localization = "localization_1";
std::string classification = "KNN";

void Camera::on_localization_1_clicked() { localization = "localization_1"; }

void Camera::on_localization_2_clicked() { localization = "localization_2"; }

void Camera::on_classification_1_clicked() { classification = "KNN"; }

void Camera::on_classification_2_clicked() { classification = "DecisionTree"; }

void Camera::on_back_9_clicked() { ui->stacked->setCurrentIndex(5); }

void Camera::on_forgot_credentials_clicked() {
    ui->stacked->setCurrentIndex(3);
}

void Camera::on_back_4_clicked() { ui->stacked->setCurrentIndex(2); }

void Camera::on_get_code_clicked() {
    /* std::string address = ui->email_code->text().toStdString();
    int temp_password = database.forgotten_password(address);
    ui->stacked->setCurrentIndex(8);
    ui->email_code->clear(); */
}
int authenticate = 0;
void Camera::on_takeImageButton_clicked() {
    if (currentIndex == "") {
        takeImage("take_image");
        std::string path = "/resources/temp.jpg";
        path = std::string(PATH_TO_RESOURCES) + path;
        cv::Mat image = cv::imread(path);
        Model model(10, 9, 0, 0, "", "Fisher", classification);
        if (authenticate == 0) {
            QMessageBox::about(
                this, "Authentication Error",
                "Your face has not been recognized, try again or go back to "
                "try logging in with password or create an account.");
        } else {
            ui->stacked->setCurrentIndex(5);
        }
    } else {
        if (num_pics == 10) {
            num_pics = 11;
            QMessageBox::about(this, "Successful Account Created",
                               "Thank you, your account is now complete.");
            ui->stacked->setCurrentIndex(5);
        } else {
            takeImage("account_photos");
            num_pics += 1;
        }
    }
}

void Camera::on_photo_library_clicked() {
    ui->stacked->setCurrentIndex(4);
    ui->camera->setCurrentIndex(0);
    ui->logout->setCurrentIndex(1);
    currentIndex = "";
}

void Camera::on_resend_code_clicked() { ui->stacked->setCurrentIndex(3); }

void Camera::on_back_10_clicked() { ui->stacked->setCurrentIndex(0); }

void Camera::on_verify_code_clicked() { ui->stacked->setCurrentIndex(9); }

void Camera::on_back_11_clicked() { ui->stacked->setCurrentIndex(0); }

void Camera::on_delete_account_clicked() { ui->stacked->setCurrentIndex(10); }

void Camera::on_change_password_2_clicked() {
    std::string username = ui->username_8->text().toStdString();
    std::string new_password = ui->new_password_8->text().toStdString();
    std::string confirm_password = ui->confirm_password_8->text().toStdString();
    //    bool check = database.change_forgotten_password(username,
    //    new_password, confirm_password); if (check == TRUE) {
    //        ui->stacked->setCurrentIndex(5);
    //}
    ui->username_8->clear();
    ui->new_password_8->clear();
    ui->confirm_password_8->clear();
}

void Camera::on_back_12_clicked() { ui->stacked->setCurrentIndex(5); }

void Camera::on_back_13_clicked() { ui->stacked->setCurrentIndex(0); }

// int count = 0;

// void Camera::buttonClicked()
//{
//     count++;
//     QLCDNumber display();.value(count);
// }

void Camera::on_log_out_clicked() { ui->stacked->setCurrentIndex(0); }

void Camera::on_create_account_clicked() { ui->stacked->setCurrentIndex(1); }
