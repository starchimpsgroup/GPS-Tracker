#include "gpstracker.h"

// Konstruktor mit Parameter

GPSTracker::GPSTracker(QObject *parent) :
    QObject(parent) {
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
}

GPSTracker::~GPSTracker() {
    delete geoPositionInfoSource;
}

void GPSTracker::startTracking() {
    startGPS();
    if(isGPSActiv()) {
        tracking = true;
    }
}

void GPSTracker::stopTracking() {
    tracking = false;
}

void GPSTracker::setTrackingInterval(int msec) {
    if(geoPositionInfoSource) {
        geoPositionInfoSource->setUpdateInterval(msec);
        trackingInterval = geoPositionInfoSource->updateInterval();
    } else {
        trackingInterval = msec;
    }
}

void GPSTracker::recordActualPosition() {
    if(isGPSActiv() && geoPositionInfoSource) {
        geoPositionInfoSource->requestUpdate(); // richtig?
        addPosition(geoPositionInfoSource->lastKnownPosition());
    }
}

void GPSTracker::startGPS() {
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

void GPSTracker::stopGPS() {
    if(isGPSActiv()) {
        geoPositionInfoSource->stopUpdates();
        changeGPSStatus(INACTIVE);
    }
}

bool GPSTracker::isGPSActiv() {
    return gpsStatus == ACTIVE || gpsStatus == RECEIVE || gpsStatus == TIMEOUT;
}

void GPSTracker::changeGPSStatus(GPSStatus status) {
    gpsStatus = status;
    emit gpsStatusChanged(status);
}

void GPSTracker::positionUpdated(QGeoPositionInfo position) {
    if(tracking){
        addPosition(position);
    }
    emit positionUpdated(Point(position));
    changeGPSStatus(RECEIVE);
}

void GPSTracker::addPosition(QGeoPositionInfo position) {
    Point point(position);
    if(points.rowCount() > 0){
        if(!points.last().equals(point)) {
            points.addPoint(point);
        }
    } else {
        points.addPoint(point);
    }
}

void GPSTracker::updateTimeout() {
    changeGPSStatus(TIMEOUT);
}
