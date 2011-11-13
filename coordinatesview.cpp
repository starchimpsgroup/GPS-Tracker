#include "coordinatesview.h"
#include "ui_coordinatesview.h"

#include <QMetaEnum>

CoordinatesView::CoordinatesView(GPSTracker * tracker, QList<QAction *> actions, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CoordinatesView)
{
    ui->setupUi(this);
    ui->menubar->addActions(actions);

    this->tracker = tracker;

    gpsStatusChanged(tracker->getGPSStatus());
    ui->format->setText("WGS84");

    connect(tracker, SIGNAL(gpsStatusChanged(GPSTracker::GPSStatus)),
            this, SLOT(gpsStatusChanged(GPSTracker::GPSStatus)));
    connect(tracker, SIGNAL(positionUpdated(Point)),
            this, SLOT(positionUpdated(Point)));

    ui->coordinatesView->setModel(tracker->getPointModel());
}

CoordinatesView::~CoordinatesView()
{
    delete ui;
}

void CoordinatesView::gpsStatusChanged(GPSTracker::GPSStatus status) {
    // http://kunalmaemo.blogspot.com/2010/05/enum-value-to-string-in-qt.html
    // http://srikanthsombhatla.wordpress.com/2010/08/13/convert-enum-to-qstring/
    QMetaObject metaObject = GPSTracker::staticMetaObject;
    QMetaEnum metaEnum = metaObject.enumerator( metaObject.indexOfEnumerator( "GPSStatus" ) );
    QString keyString = metaEnum.valueToKey( status );

    ui->status->setText("Status: " + keyString);
}

void CoordinatesView::positionUpdated(Point point) {
    ui->longitude->setText(QString::number(point.getLongitude()));
    ui->latitude->setText(QString::number(point.getLatitude()));
    ui->altitude->setText(QString::number(point.getAltitude()));
}

void CoordinatesView::on_actionWGS84_triggered() {
    tracker->getPointModel()->setFormat(Point::WGS84);
    ui->coordinatesView->repaint();
    ui->format->setText("WGS84");
}

void CoordinatesView::on_actionECEF_triggered() {
    tracker->getPointModel()->setFormat(Point::ECEF);
    ui->coordinatesView->repaint();
    ui->format->setText("ECEF");
}

void CoordinatesView::on_actionENU_triggered() {
    tracker->getPointModel()->setFormat(Point::ENU);
    ui->coordinatesView->repaint();
    ui->format->setText("ENU");
}
