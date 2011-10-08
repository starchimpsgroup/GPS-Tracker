#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QGeoPositionInfo>

using namespace QtMobility;

class Point
{
public:
    Point(double longitude,
          double latitude,
          double altitude);

    Point(const QGeoPositionInfo * position);

    void setLongitude(double longitude){this->longitude = longitude;}
    double getLongitude(){return longitude;}

    void setLatitude(double latitude){this->latitude = latitude;}
    double getLatitude(){return latitude;}

    void setAltitude(double altitude){this->altitude = altitude;}
    double getAltitude(){return altitude;}

    void setInfoText(QString text){infoText = text;}
    QString getInfoText(){return infoText;}

    bool equals(const Point * point);

private:
    double longitude;
    double latitude;
    double altitude;

    QString infoText;
};

#endif // POINT_H
