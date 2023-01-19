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
#include <QMediaRecorder>
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
};

//class Photo_Camera : public QMainWindow
//{
//    Q_OBJECT

//public:
//    Photo_Camera();

//public slots:
//    void saveMetaData();

//private slots:
//    void setCamera_2(const QCameraDevice &cameraDevice);
//    void startCamera_2();
//    void stopCamera_2();
//    void takeImage_2();
//    void displayCaptureError_2(int, QImageCapture::Error, const QString &errorString);

//    void configureCaptureSettings_2();
//    void configureImageSettings_2();

//    void displayRecorderError();
//    void displayCameraError();
//    void updateCameraDevice_2(QAction *action);

//    void updateCameraActive_2(bool active);
//    void setExposureCompensation_2(int index);
//    void processCapturedImage_2(int requestId, const QImage &img);

//    void displayViewfinder_2();
//    void displayCapturedImage_2();

//    void readyForCapture_2(bool ready);
//    void imageSaved_2(int id, const QString &fileName);
//    void updateCameras_2();

//    void showMetaDataDialog_2();

//protected:
//    void keyPressEvent_2(QKeyEvent *event) ;
//    void closeEvent_2(QCloseEvent *event) ;

//private:
//    Ui::Camera *ui_2;
//    QMediaDevices p_devices;
//    QScopedPointer<QImageCapture> p_imageCapture;
//    QMediaCaptureSession p_captureSession;
//    QScopedPointer<QCamera> p_camera;
//    QScopedPointer<QMediaRecorder> p_mediaRecorder;

//    bool p_isCapturingImage = false;
//    bool p_applicationExiting = false;
//    bool p_doImageCapture = true;

//    MetaDataDialog *p_metaDataDialog = nullptr;
//};

#endif
