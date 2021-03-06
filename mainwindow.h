#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "gpstracker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private:
    GPSTracker * tracker;

private slots:
    void startGPS(){tracker->startGPS();}
    void stopGPS(){tracker->stopGPS();}
    void startTracking(){tracker->startTracking();}
    void stopTracking(){tracker->stopTracking();}
    void recordActualPosition(){tracker->recordActualPosition();}
    void satelliteinfo();
};

#endif // MAINWINDOW_H
