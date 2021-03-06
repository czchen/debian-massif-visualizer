/****************************************************************************
 ** Copyright (C) 2007 Klaralvdalens Datakonsult AB.  All rights reserved.
 **
 ** This file is part of the KD Chart library.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License versions 2.0 or 3.0 as published by the Free Software
 ** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
 ** included in the packaging of this file.  Alternatively you may (at
 ** your option) use any later version of the GNU General Public
 ** License if such license has been publicly approved by
 ** Klarälvdalens Datakonsult AB (or its successors, if any).
 ** 
 ** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
 ** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE. Klarälvdalens Datakonsult AB reserves all rights
 ** not expressly granted herein.
 ** 
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 **********************************************************************/

#include "KDChartValueTrackerAttributes.h"

#include <KDABLibFakes>
#include <QPen>
#include <QSizeF>
#include <QBrush>

#define d d_func()

using namespace KDChart;

class ValueTrackerAttributes::Private
{
    friend class ValueTrackerAttributes;
    public:
        Private();
    private:
        QPen pen;
        QSizeF markerSize;
        bool enabled;
        QBrush areaBrush;
};

ValueTrackerAttributes::Private::Private()
    : pen( QPen( QColor( 80, 80, 80, 200 ) ) ),
      markerSize( QSizeF( 6.0, 6.0 ) ),
      enabled( false ),
      areaBrush( QBrush() )
{
}


ValueTrackerAttributes::ValueTrackerAttributes()
    : _d( new Private() )
{
}

ValueTrackerAttributes::ValueTrackerAttributes( const ValueTrackerAttributes& r )
    : _d( new Private( *r.d ) )
{
}

ValueTrackerAttributes & ValueTrackerAttributes::operator=( const ValueTrackerAttributes& r )
{
    if( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

ValueTrackerAttributes::~ValueTrackerAttributes()
{
    delete _d; _d = 0;
}


bool ValueTrackerAttributes::operator==( const ValueTrackerAttributes& r ) const
{
    return ( pen() == r.pen() &&
             areaBrush() == r.areaBrush() &&
             markerSize() == r.markerSize() &&
             isEnabled() == r.isEnabled() );
}

void ValueTrackerAttributes::setPen( const QPen& pen )
{
    d->pen = pen;
}

QPen ValueTrackerAttributes::pen() const
{
    return d->pen;
}

void ValueTrackerAttributes::setAreaBrush( const QBrush& brush )
{
    d->areaBrush = brush;
}

QBrush ValueTrackerAttributes::areaBrush() const
{
    return d->areaBrush;
}

void ValueTrackerAttributes::setMarkerSize( const QSizeF& size )
{
    d->markerSize = size;
}

QSizeF ValueTrackerAttributes::markerSize() const
{
    return d->markerSize;
}

void ValueTrackerAttributes::setEnabled( bool enabled )
{
    d->enabled = enabled;
}

bool ValueTrackerAttributes::isEnabled() const
{
    return d->enabled;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KDChart::ValueTrackerAttributes& va)
{
    dbg << "KDChart::ValueTrackerAttributes("
            << "pen="<<va.pen()
            << "markerSize="<<va.markerSize()
            << "enabled="<<va.isEnabled()
            << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
