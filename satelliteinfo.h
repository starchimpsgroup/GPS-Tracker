#ifndef SATELLITEINFO_H
#define SATELLITEINFO_H

#include <QMessageBox>
#include <QGeoPositionInfoSource>
#include <QGeoSatelliteInfoSource>

using namespace QtMobility;

namespace Ui {
class SatelliteInfo;
}

class SatelliteInfo : public QMessageBox
{
    Q_OBJECT
public:
    explicit SatelliteInfo(QWidget *parent = 0);

private:
//    struct PolarCoordiante{
//        double r;
//        double phi;
//        double lambda;
//    };

//    PolarCoordiante c2p(const QGeoCoordinate &coordiante);
    void updateText();

private:
    int inUse;
    int inView;

private slots:
    void satellitesInUseUpdated  ( const QList<QGeoSatelliteInfo> & satellites );
    void satellitesInViewUpdated ( const QList<QGeoSatelliteInfo> & satellites );
//    void positionUpdated ( const QGeoPositionInfo & update );
};



#endif // SATELLITEINFO_H
