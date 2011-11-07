#include "camera.h"

Camera::Camera(QWidget *parent) :
    QCameraViewfinder(parent)
{
    //    QByteArray cameraDevice = QCamera::availableDevices()[0];
    camera = new QCamera;
    camera->setViewfinder(this);

    //    recorder = new QMediaRecorder(camera);
    //    imageCapture = new QCameraImageCapture(camera);

    camera->setCaptureMode(QCamera::CaptureStillImage);

    //    //on half pressed shutter button
    //    camera->searchA{QCameraFocus::FocusMode}{ndLock();

    //    //on shutter button pressed
    //    imageCapture->capture();

    //    //on shutter button released
    //    camera->unlock();
}

void Camera::startCamera() {
    camera->start();
}
