#include "point.h"

Point::Point(double longitude,
             double latitude,
             double altitude) {
    this->longitude = longitude;
    this->latitude = latitude;
    this->altitude = altitude;
}

Point::Point(const QGeoPositionInfo &position) {
    QGeoCoordinate coordinate = position.coordinate();
    this->longitude = coordinate.longitude();
    this->latitude = coordinate.latitude();
    this->altitude = coordinate.altitude();
}

bool Point::equals(const Point &point) {
    return point.longitude == longitude && point.latitude == latitude && point.altitude == altitude;
}
