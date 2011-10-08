#include "gpstracker.h"

// Konstruktor mit Parameter

GPSTracker::GPSTracker(QObject *parent) :
    QObject(parent){
    geoPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);
    // emit funktioniert erst nach dem Konstruktor
    if(geoPositionInfoSource) {
        connect(geoPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(positionUpdated(QGeoPositionInfo)));
        connect(geoPositionInfoSource, SIGNAL(updateTimeout()),
                this, SLOT(updateTimeout()));
        changeGPSStatus(INACTIVE);
    } else {
        changeGPSStatus(ERROR);
    }

    trackingInterval = 500;
    tracking = false;

    points = new QList<Point>();
}

GPSTracker::~GPSTracker(){
    delete geoPositionInfoSource;

//    qDeleteAll(points->begin(), points->end());
    delete points;
}

void GPSTracker::startTracking(){
    startGPS();
    if(isGPSActiv()) {
        tracking = true;
    }
}

void GPSTracker::stopTracking(){
    tracking = false;
}

void GPSTracker::setTrackingInterval(int msec){
    if(geoPositionInfoSource) {
        geoPositionInfoSource->setUpdateInterval(msec);
        trackingInterval = geoPositionInfoSource->updateInterval();
    } else {
        trackingInterval = msec;
    }
}

void GPSTracker::recordActualPosition(){
    if(geoPositionInfoSource) {
        geoPositionInfoSource->requestUpdate(); // richtig?
        addPoint(Point(&geoPositionInfoSource->lastKnownPosition()));
    }
}

void GPSTracker::startGPS(){
    if(geoPositionInfoSource) {
        if(!isGPSActiv()){
            setTrackingInterval(trackingInterval);
            geoPositionInfoSource->startUpdates();
            changeGPSStatus(ACTIVE);
        }
    } else {
        changeGPSStatus(ERROR);
    }
}

void GPSTracker::stopGPS(){
    if(isGPSActiv()) {
        geoPositionInfoSource->stopUpdates();
        changeGPSStatus(INACTIVE);
    }
}

bool GPSTracker::isGPSActiv(){
    return gpsStatus == ACTIVE || gpsStatus == RECEIVE || gpsStatus == TIMEOUT;
}

void GPSTracker::changeGPSStatus(GPSStatus status){
    gpsStatus = status;
    emit gpsStatusChanged(status);
}

void GPSTracker::positionUpdated(QGeoPositionInfo position)
{
    Point point(&position);
    if(tracking){
        addPoint(point);
    }
    emit positionUpdated(point);
    changeGPSStatus(RECEIVE);
}

void GPSTracker::addPoint(Point point){
    if(points->size() > 0){
        // letzter Punkt mit aktuellem vergleichen
        if(points->last().equals(&point)) {
            //            delete point;
        } else {
            points->append(point);
        }
    } else {
        points->append(point);
    }
}

void GPSTracker::updateTimeout(){
    changeGPSStatus(TIMEOUT);
}
