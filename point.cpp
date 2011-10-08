#include "point.h"

Point::Point(double longitude,
             double latitude,
             double altitude){
    this->longitude = longitude;
    this->latitude = latitude;
    this->altitude = altitude;
}

Point::Point(const QGeoPositionInfo * position){
    this->longitude = position->coordinate().longitude();
    this->latitude = position->coordinate().latitude();
    this->altitude = position->coordinate().altitude();
}

bool Point::equals(const Point * point){
    return point->longitude == longitude && point->latitude == latitude && point->altitude == altitude;
}
