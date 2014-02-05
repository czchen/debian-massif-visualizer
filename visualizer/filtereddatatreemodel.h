/*
   This file is part of Massif Visualizer

   Copyright 2010 Milian Wolff <mail@milianw.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef MASSIF_FILTEREDDATATREEMODEL_H
#define MASSIF_FILTEREDDATATREEMODEL_H

#include <QtGui/QSortFilterProxyModel>

#include "visualizer_export.h"

namespace Massif {

class DataTreeModel;

/**
 * Filter class for DataTreeModel
 */
class VISUALIZER_EXPORT FilteredDataTreeModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit FilteredDataTreeModel(DataTreeModel* parent);

public slots:
    void setFilter(const QString& needle);

protected:
    /// true for any branch that has an item in it that matches m_needle
    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
    /// always true
    virtual bool filterAcceptsColumn(int source_column, const QModelIndex& source_parent) const;

private:
    /// we don't want that
    virtual void setSourceModel(QAbstractItemModel* sourceModel);

    /// search string that should be contained in the data (case insensitively)
    QString m_needle;
};

}

#endif // MASSIF_FILTEREDDATATREEMODEL_H
