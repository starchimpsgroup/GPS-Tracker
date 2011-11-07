#ifndef SATELLITEINFO_H
#define SATELLITEINFO_H

#include <QMainWindow>
#include <QGeoPositionInfoSource>
#include <QGeoSatelliteInfoSource>

using namespace QtMobility;

namespace Ui {
class SatelliteInfo;
}

class SatelliteInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit SatelliteInfo(QWidget *parent = 0);
    ~SatelliteInfo();

private:
    Ui::SatelliteInfo *ui;

    struct PolarCoordiante{
        double r;
        double phi;
        double lambda;
    };

    PolarCoordiante c2p(const QGeoCoordinate &coordiante);

private slots:
    void satellitesInUseUpdated ( const QList<QGeoSatelliteInfo> & satellites );
    void satellitesInViewUpdated ( const QList<QGeoSatelliteInfo> & satellites );
    void positionUpdated ( const QGeoPositionInfo & update );
};



#endif // SATELLITEINFO_H
