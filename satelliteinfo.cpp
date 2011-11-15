#include "satelliteinfo.h"
#include "ui_satelliteinfo.h"
#include <cmath>
#include "camera.h"

SatelliteInfo::SatelliteInfo(QWidget *parent) :
    QMessageBox(parent)
{
    QGeoSatelliteInfoSource * satelliteInfoSource = QGeoSatelliteInfoSource::createDefaultSource(this);
    connect(satelliteInfoSource, SIGNAL(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)),
            SLOT(satellitesInUseUpdated(QList<QGeoSatelliteInfo>)));
    connect(satelliteInfoSource, SIGNAL(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)),
            SLOT(satellitesInViewUpdated(QList<QGeoSatelliteInfo>)));

/*    QGeoPositionInfoSource * positionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);

    connect(positionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
            SLOT(positionUpdated(QGeoPositionInfo)));*/

//    positionInfoSource->startUpdates();

    satelliteInfoSource->startUpdates();

    inUse  = 0;
    inView = 0;
    updateText();

//    Camera * camera = new Camera(this);
//    ui->menubar->addAction("Start Camera", camera, SLOT(startCamera()));
//    setCentralWidget(camera);
}

void SatelliteInfo::satellitesInUseUpdated(const QList<QGeoSatelliteInfo> &satellites)
{
    inUse = satellites.count();
    updateText();
//    ui->satellitesUse->setText(QString::number(satellites.count()));
}

void SatelliteInfo::satellitesInViewUpdated(const QList<QGeoSatelliteInfo> &satellites)
{
    inView = satellites.count();
    updateText();
//    ui->satellitesView->setText(QString::number(satellites.count()));
}

void SatelliteInfo::updateText() {
    setText("Satelliten in Sicht: "    + QString::number(inView) + "\n" +
            "Satelliten in Gebrauch: " + QString::number(inUse));
}

//void SatelliteInfo::positionUpdated(const QGeoPositionInfo &update)
//{
//    ui->precision->setText(QString::number(update.attribute(QGeoPositionInfo::HorizontalAccuracy)));
//    PolarCoordiante coordiante = c2p(update.coordinate());
//    ui->phi->setText(QString::number(coordiante.phi));
//    ui->lambda->setText(QString::number(coordiante.lambda));
//    ui->height->setText(QString::number(update.coordinate().altitude()));
//}

//SatelliteInfo::PolarCoordiante SatelliteInfo::c2p(const QGeoCoordinate &coordiante)
//{
//    double lon = coordiante.longitude();
//    double lat = coordiante.latitude();
//    double alt = coordiante.altitude();

//    PolarCoordiante p;
//    p.r = sqrt(lon*lon+lat*lon+alt*alt);
//    p.phi = atan2(lon,lat);
//    p.lambda = acos(alt/p.r);

//    return p;
//}
