/*
  GNU Gama Qt based GUI
  Copyright (C) 2013 Ales Cepek <cepek@gnu.org>

  This file is part of GNU Gama.

  GNU Gama is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GNU Gama is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Gama.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAMALOCALOBSERVATIONTABLEMODEL_H
#define GAMALOCALOBSERVATIONTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <gnu_gama/local/network.h>

typedef GNU_gama::local::Observation     Observation;
typedef GNU_gama::local::Angle           Angle;
typedef GNU_gama::Cluster<Observation>   Cluster;
typedef GNU_gama::List<Cluster*>         ClusterList;
typedef GNU_gama::local::ObservationList ObservationList;
typedef GNU_gama::local::LocalNetwork    LocalNetwork;

class ObservationTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ObservationTableModel(GNU_gama::local::LocalNetwork* lnt,
                          QObject *parent=0);

    // abstract methods from QAbstractTableModel
    int        rowCount   (const QModelIndex &parent) const;
    int        columnCount(const QModelIndex &parent) const;
    QVariant   data       (const QModelIndex &index, int role) const;

    // implementation of header section
    QVariant   headerData (int section, Qt::Orientation orientation,
                           int role = Qt::DisplayRole) const;
/*
    // resizeable data
    bool       setData (const QModelIndex &index,
                        const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // columns are static in GamaLocalPointModel, only rows
    // operations need to be implemented
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
*/
private:
    GNU_gama::local::LocalNetwork*    lnet;
    GNU_gama::local::ObservationData& obsData;

    enum RowType  { clusterHeader, clusterTail, obsRow };
    enum ColIndx  { indAdj, indFrom, indTo, indName, indVal, indStdev,
                    indColumnCount };
    enum ObsNames { indDist,  indDir,   indAngle, indHdiff,
                    indXdiff, indYdiff, indZdiff, indX, indY, indZ,
                    indSdist, indZangle };

    struct ObsInfo
    {
        ObsInfo();

        QString from();
        QString to();
        QString name();
        QVariant value(LocalNetwork* lnet);
        QVariant stdDev(LocalNetwork* lnet);

        static QStringList obsNames;

        RowType            rowType;
        const Cluster     *cluster;
        QString            clusterName;
        int                clusterIndex;
        const Observation *observation;
        int                observationNameIndex;
        int                adjustmentIndex;
        const Angle       *angle;
        bool               angular;
    };

    QVector<ObsInfo> obsMap;

    void initObsMap();

signals:
    void warning(QString);
};

#endif // GAMALOCALOBSERVATIONTABLEMODEL_H