#ifndef GPSTRACKER_H
#define GPSTRACKER_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include "pointmodel.h"
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

    inline bool isTracking(){return tracking;}
    inline void setTrackingInterval(int msec);
    inline int getTrackingInterval(){return trackingInterval;}

    inline bool isGPSActiv();
    inline GPSStatus getGPSStatus(){return gpsStatus;}

    inline QGeoPositionInfoSource * getQGeoPositionInfoSource(){return geoPositionInfoSource;}
    inline PointModel * getPointModel(){return &points;}

    inline double getHorizontalAccuracy() {return horizontalAccuracy;}
    inline double getVerticalAccuracy()   {return verticalAccuracy;}

signals:
    void gpsStatusChanged(GPSTracker::GPSStatus status);
    void positionUpdated(Point point);

private:
    inline void changeGPSStatus(GPSStatus status);
    void addPosition(QGeoPositionInfo position);

private:
    QGeoPositionInfoSource * geoPositionInfoSource;
    PointModel points;
    GPSStatus gpsStatus;
    int trackingInterval;
    bool tracking;
    double horizontalAccuracy;
    double verticalAccuracy;

private slots:
    void positionUpdated(QGeoPositionInfo position);
    void updateTimeout();

public slots:
    void startGPS();
    void stopGPS();
    void startTracking();
    void stopTracking();
    void recordActualPosition();
};

#endif // GPSTRACKER_H
