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

#ifndef MASSIF_PARSER_H
#define MASSIF_PARSER_H

class QIODevice;

#include <QtCore/QString>
#include <QtCore/QStringList>

#include "massifdata_export.h"

namespace Massif {

class FileData;

/**
 * This class parses a Massif output file and stores it's information.
 */
class MASSIFDATA_EXPORT Parser
{
public:
    Parser();
    ~Parser();

    /**
     * Parse @p file and return a FileData structure representing the data.
     *
     * @p customAllocators list of wildcard patterns used to find custom allocators
     *
     * @return Data or null if file could not be parsed.
     *
     * @note The caller has to delete the data afterwards.
     */
    FileData* parse(QIODevice* file,
                    const QStringList& customAllocators = QStringList());

    /**
     * Returns the number of the line which could not be parsed or -1 if no error occurred.
     */
    int errorLine() const;
    /**
     * Returns the line which could not be parsed.
     */
    QString errorLineString() const;

private:
    int m_errorLine;
    QString m_errorLineString;
};

}

#endif // MASSIF_PARSER_H
