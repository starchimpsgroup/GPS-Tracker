#ifndef GPSTRACKER_H
#define GPSTRACKER_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include "point.h"

using namespace QtMobility;

class GPSTracker : public QObject
{
    Q_OBJECT
    Q_ENUMS(GPSStatus)
public:
    enum GPSStatus {
        INACTIVE,
        ACTIVE,
        RECEIVE,
        TIMEOUT,
        ERROR
    };

    explicit GPSTracker(QObject *parent = 0);
    ~GPSTracker();

    void startTracking();
    void stopTracking();
    bool isTracking(){return tracking;}
    void setTrackingInterval(int msec);
    int getTrackingInterval(){return trackingInterval;}
    void recordActualPosition();

    void startGPS();
    void stopGPS();
    bool isGPSActiv();
    GPSStatus getGPSStatus(){return gpsStatus;}

    QGeoPositionInfoSource * getQGeoPositionInfoSource(){return geoPositionInfoSource;}
    QList<Point> * getPoints(){return points;}

signals:
    void gpsStatusChanged(GPSTracker::GPSStatus status);
    void positionUpdated(Point point);

private:
    void changeGPSStatus(GPSStatus status);
    void addPoint(Point point);

private:
    QGeoPositionInfoSource * geoPositionInfoSource;
    QList<Point> * points;
    GPSStatus gpsStatus;
    int trackingInterval;
    bool tracking;

private slots:
    void positionUpdated(QGeoPositionInfo position);
    void updateTimeout();
};

#endif // GPSTRACKER_H
