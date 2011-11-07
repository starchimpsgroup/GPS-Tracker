#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMediaRecorder>

class Camera : public QCameraViewfinder
{
    Q_OBJECT
public:
    explicit Camera(QWidget *parent = 0);

private:
    QCamera * camera;
    QCameraImageCapture * imageCapture;
    QMediaRecorder * recorder;

signals:

public slots:
    void startCamera();
};

#endif // CAMERA_H
