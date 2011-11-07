#include "pointmodel.h"

PointModel::PointModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int PointModel::rowCount(const QModelIndex &parent) const
{
    return points.count();
}

QVariant PointModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
        case Qt::DisplayRole:
        return points.at(index.row()).text();
    }

    return QVariant();
}

void PointModel::addPoint(const Point &point) {
    beginInsertRows(QModelIndex(),points.count(),points.count());
    points.append(point);
    endInsertRows();
}
