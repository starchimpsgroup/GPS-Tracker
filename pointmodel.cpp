#include "pointmodel.h"

PointModel::PointModel(QObject *parent) :
    QAbstractListModel(parent)
{
    format = Point::WGS84;
}

int PointModel::rowCount(const QModelIndex &parent) const
{
    return points.count();
}

QVariant PointModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
        Point point = points.at(index.row());

        switch(format) {
            case Point::WGS84:
                return point.text();
            break;
            case Point::ECEF:
                return Point::WGS2ECEF(point).text();
            break;
            case Point::ENU:
                return Point::WGS2ENU(points.first(), point).text();
            break;
            case Point::DHDN:
            break;
        }
    }

    return QVariant();
}

void PointModel::addPoint(const Point &point)
{
    beginInsertRows(QModelIndex(),points.count(),points.count());
    points.append(point);
    endInsertRows();
}
