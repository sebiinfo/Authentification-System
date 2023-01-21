// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CAMERA_H
#define CAMERA_H

#include "../Database/database.hpp"

#include <QStackedWidget>
#include <QAudioInput>
#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QMediaMetaData>
#include <QPushButton>
#include <QMediaRecorder>
#include <QLCDNumber>
#include <QGraphicsAnchorLayout>
#include <QScopedPointer>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Camera;
}

//namespace Ui {
//class Photo_Camera;
//}
class QActionGroup;
QT_END_NAMESPACE

class MetaDataDialog;

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    Camera();

public slots:
    void saveMetaData();

private slots:
    void setCamera(const QCameraDevice &cameraDevice);

    void startCamera();
    void stopCamera();

    void record();
    void pause();
    void stop();
    void setMuted(bool);

    void takeImage();
    void displayCaptureError(int, QImageCapture::Error, const QString &errorString);

    void configureCaptureSettings();
    void configureVideoSettings();
    void configureImageSettings();

    void displayRecorderError();
    void displayCameraError();

    void updateCameraDevice(QAction *action);

    void updateCameraActive(bool active);
    // void updateCaptureMode();
    // void updateRecorderState(QMediaRecorder::RecorderState state);
    void setExposureCompensation(int index);

    void updateRecordTime();

    void processCapturedImage(int requestId, const QImage &img);

    void displayViewfinder();
    void displayCapturedImage();

    void readyForCapture(bool ready);

    void imageSaved(int id, const QString &fileName);

    void updateCameras();

    void showMetaDataDialog();

    void on_register_2_clicked();

    void on_face_recognition_clicked();

    void on_password_clicked();

    void on_back_clicked();

    void on_back_2_clicked();

    void on_back_3_clicked();

    void on_login_2_clicked();

    void on_create_2_clicked();

    void on_new_password_clicked();

    void on_update_password_clicked();

    void on_change_email_clicked();

    void on_update_email_clicked();

    void on_back_7_clicked();

    void on_back_8_clicked();

    void on_localization_1_clicked();

    void on_localization_2_clicked();

    void on_vectorization_1_clicked();

    void on_vectorization_2_clicked();

    void on_classification_1_clicked();

    void on_classification_2_clicked();

    void on_create_account_clicked();

    void on_back_9_clicked();

    void on_forgot_credentials_clicked();

    void on_back_4_clicked();

    void on_get_code_clicked();

    void on_takeImageButton_clicked();

    void on_photo_library_clicked();

    void on_resend_code_clicked();

    void on_back_10_clicked();

    void on_verify_code_clicked();

    void on_back_11_clicked();

    void on_delete_account_5_clicked();

    void on_delete_account_clicked();

    void on_change_password_2_clicked();

    void on_back_12_clicked();

    void on_back_13_clicked();

    void on_localization_1_toggled(bool checked);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Camera *ui;
    Database database;
    QActionGroup *videoDevicesGroup = nullptr;
    QMediaDevices m_devices;
    QScopedPointer<QImageCapture> m_imageCapture;
    QMediaCaptureSession m_captureSession;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QAudioInput> m_audioInput;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;
    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;
    bool m_doImageCapture = true;

    MetaDataDialog *m_metaDataDialog = nullptr;
    void buttonClicked();
};

#endif
