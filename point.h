#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QGeoPositionInfo>
#include <QListWidgetItem>
#include <cmath>

#define A 6378137.0
#define B A*(1-F)
#define F 1.0/298.257223563
//#define E sqrt((A*A - B*B) / (A*A))
//#define E2 E*E
#define E2 2*F-F*F
//#define EI pow((A*A - B*B) / (B*B), 0.5)

using namespace QtMobility;

class Point : public QListWidgetItem
{
public:
    enum GPSFormat {
        WGS84,
        ECEF,
        ENU,
        DHDN
    };

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
        // http://dspace.dsto.defence.gov.au/dspace/bitstream/1947/3538/1/DSTO-TN-0432.pdf
        double lat = point.latitude * M_PI / 180.0;
        double lon = point.longitude * M_PI / 180.0;
        double alt = point.altitude;

        double chi = sqrt(1 - E2 * sin(lat) * sin(lat));
        double n = A / chi;

        double x = (n + alt) * cos(lat) * cos(lon);
        double y = (n + alt) * cos(lat) * sin(lon);
        double z = ((1 - E2) * n + alt) * sin(lat);
//        double z = (((B * B) / (A * A)) * n + alt) * sin(lat);

        return Point(x, y, z, Point::ECEF);
    }

    static Point WGS2ENU(Point reference, Point position) {
        return Point::ECEF2ENU(reference, Point::WGS2ECEF(reference), Point::WGS2ECEF(position));
    }

    static Point ECEF2ENU(Point referenceWGS84, Point referenceECEF, Point positionECEF) {
        // http://en.wikipedia.org/wiki/Geodetic_system
        // http://www.ottmarlabonde.de/L1/Datumstransformation.htm
        double lat = referenceWGS84.latitude * M_PI / 180.0;
        double lon = referenceWGS84.longitude * M_PI / 180.0;

        double pX = positionECEF.latitude  - referenceECEF.latitude;
        double pY = positionECEF.longitude - referenceECEF.longitude;
        double pZ = positionECEF.altitude  - referenceECEF.altitude;

        // Line 1
        double a1 = -sin(lon);
        double b1 = cos(lon);
        double c1 = 0.0;

        // Line 2
        double a2 = -sin(lat)*cos(lon);
        double b2 = -sin(lat)*sin(lon);
        double c2 = cos(lat);

        // Line 3
        double a3 = cos(lat)*cos(lon);
        double b3 = cos(lat)*sin(lon);
        double c3 = sin(lat);

        double x = a1 * pX + b1 * pY + c1 * pZ;
        double y = a2 * pX + b2 * pY + c2 * pZ;
        double z = a3 * pX + b3 * pY + c3 * pZ;

        return Point(x, y, z, Point::ENU);
    }

    static Point ECEF2DHDN() {
        return Point(0, 0, 0);
    }

private:
    double latitude;
    double longitude;
    double altitude;

    GPSFormat format;

    QString infoText;
};

#endif // POINT_H
