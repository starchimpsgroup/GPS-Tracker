#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QGeoPositionInfo>
#include <QListWidgetItem>
#include <cmath>

#define A 6378137.0
#define B A*(1-F)
#define F 1/298.257223563
#define E sqrt((A*A - B*B) / (A*A))
#define E2 E*E
//#define E2 2*F-F*F
//#define EI pow((A*A - B*B) / (B*B), 0.5)

using namespace QtMobility;

class Point : public QListWidgetItem
{
public:
    typedef enum GPSFormat {
        WGS84,
        ECEF,
        ENU,
        DHDN
    }
    GPSFormat;

    Point(double latitude  = 0.0,
          double longitude = 0.0,
          double altitude  = 0.0,
          GPSFormat format = Point::WGS84);

    Point(const QGeoPositionInfo &position);

    void setLongitude(double longitude){this->longitude = longitude;}
    double getLongitude(){return longitude;}

    void setLatitude(double latitude){this->latitude = latitude;}
    double getLatitude(){return latitude;}

    void setAltitude(double altitude){this->altitude = altitude;}
    double getAltitude(){return altitude;}

    void setInfoText(QString text){infoText = text;}
    QString getInfoText(){return infoText;}

    bool equals(const Point &point);

    const QString text(GPSFormat format) const;

    const QString text() const;

    static Point WGS2ECEF(Point point) {
        // http://www.microem.ru/pages/u_blox/tech/dataconvert/GPS.G1-X-00006.pdf
        // http://www.sysense.com/products/ecef_lla_converter/index.html
        double chi = sqrt(1 - E2 * sin(point.latitude) * sin(point.latitude));
        double n = A / chi;
        double x = (n + point.altitude) * cos(point.latitude) * cos(point.longitude);
        double y = (n + point.altitude) * cos(point.latitude) * sin(point.longitude);
        double z = (((B * B) / (A * A)) * n + point.altitude) * sin(point.latitude);

        qDebug("%f,%f,%f", x, y, z);
        qDebug("%f,%f,%f", point.latitude, point.longitude, point.altitude);

        return Point(x, y, z, Point::ECEF);
    }

private:
    double latitude;
    double longitude;
    double altitude;

    GPSFormat format;

    QString infoText;
};

#endif // POINT_H
