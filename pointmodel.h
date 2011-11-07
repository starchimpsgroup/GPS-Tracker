#ifndef POINTMODEL_H
#define POINTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "point.h"

class PointModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PointModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    Point &last() {return points.last();}

signals:

public slots:
    void addPoint(const Point &point);

private:
    QList<Point> points;

};

#endif // POINTMODEL_H
