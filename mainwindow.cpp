#include "mainwindow.h"
#include "coordinatesview.h"
#include "satelliteinfo.h"

#include <QtCore/QCoreApplication>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QList<QAction *> actions;
    QAction * action = new QAction(tr("Start GPS"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(startGPS()));
    actions.append(action);

    action = new QAction(tr("Stop GPS"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(stopGPS()));
    actions.append(action);

    action = new QAction(tr("Start Tracking"), this);
    connect(action, SIGNAL(triggered()), this, SLOT(startTracking()));
    actions.append(action);

    tracker = new GPSTracker(this);
    CoordinatesView * coordinatesView = new CoordinatesView(tracker, actions, this);
    coordinatesView->showMaximized();

//    SatelliteInfo * satelliteInfo = new SatelliteInfo(this);
//    satelliteInfo->showMaximized();
}

MainWindow::~MainWindow(){
    delete tracker;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}

void MainWindow::startGPS()
{
    tracker->startGPS();
}

void MainWindow::stopGPS()
{
    tracker->stopGPS();
}

void MainWindow::startTracking() {
    tracker->startTracking();
}
