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

#ifndef DATAMODELTEST_H
#define DATAMODELTEST_H

#include <QtCore/QObject>

namespace Massif {
class DataModel;
}

class DataModelTest : public QObject
{
    Q_OBJECT

private slots:
    void parseFile();
    void testUtils();
    void shortenTemplates_data();
    void shortenTemplates();

private:
    Massif::DataModel* m_model;
};

#endif // DATAMODELTEST_H
