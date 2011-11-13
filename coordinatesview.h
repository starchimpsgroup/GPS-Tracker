#ifndef COORDINATESVIEW_H
#define COORDINATESVIEW_H

#include <QMainWindow>
#include "gpstracker.h"

namespace Ui {
class CoordinatesView;
}

class CoordinatesView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CoordinatesView(GPSTracker * tracker, QList<QAction *> actions, QWidget *parent = 0);
    ~CoordinatesView();

private:
    Ui::CoordinatesView * ui;
    GPSTracker * tracker;

private slots:
    void gpsStatusChanged(GPSTracker::GPSStatus status);
    void positionUpdated(Point point);

    void on_actionWGS84_triggered();
    void on_actionECEF_triggered();
    void on_actionENU_triggered();
};

#endif // COORDINATESVIEW_H
