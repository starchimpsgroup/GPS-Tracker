#include "point.h"

Point::Point(double latitude,
             double longitude,
             double altitude,
             GPSFormat format) {
    this->latitude  = latitude;
    this->longitude = longitude;
    this->altitude  = altitude;
    this->format    = format;
}

Point::Point(const QGeoPositionInfo &position) {
    QGeoCoordinate coordinate = position.coordinate();
    this->latitude  = coordinate.latitude();
    this->longitude = coordinate.longitude();
    this->altitude  = coordinate.altitude();
    this->format    = Point::WGS84;
}

bool Point::equals(const Point &point) {
    return point.latitude  == latitude &&
           point.longitude == longitude &&
           point.altitude  == altitude &&
           point.format    == format;
}

const QString Point::text() const {
    return QString("%1 %2 %3").arg(latitude,  0, 'f', 3).
                               arg(longitude, 0, 'f', 3).
                               arg(altitude,  0, 'f', 3);
}

const QString Point::text(GPSFormat format) const {
    switch(format) {
        case Point::WGS84:
            return text();
        break;
        case Point::ECEF:
            return Point::WGS2ECEF(*this).text();
        break;
        case Point::ENU:
        break;
        case Point::DHDN:
        break;
    }
}
