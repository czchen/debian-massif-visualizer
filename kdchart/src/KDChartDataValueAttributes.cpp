/****************************************************************************
 ** Copyright (C) 2007 Klarälvdalens Datakonsult AB.  All rights reserved.
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

#include "KDChartDataValueAttributes.h"

#include <QVariant>
#include <QDebug>
#include "KDChartRelativePosition.h"
#include "KDChartPosition.h"
#include <KDChartTextAttributes.h>
#include <KDChartFrameAttributes.h>
#include <KDChartBackgroundAttributes.h>
#include <KDChartMarkerAttributes.h>

#include <KDABLibFakes>

// FIXME till
#define KDCHART_DATA_VALUE_AUTO_DIGITS 4


#define d d_func()

using namespace KDChart;

class DataValueAttributes::Private
{
    friend class DataValueAttributes;
public:
    Private();
private:
    bool visible;
    TextAttributes textAttributes;
    FrameAttributes frameAttributes;
    BackgroundAttributes backgroundAttributes;
    MarkerAttributes markerAttributes;
    int decimalDigits;
    QString prefix;
    QString suffix;
    QString dataLabel;
    int powerOfTenDivisor;
    bool showInfinite;
    RelativePosition negativeRelPos;
    RelativePosition positiveRelPos;
    bool showRepetitiveDataLabels;
    bool showOverlappingDataLabels;
};

DataValueAttributes::Private::Private() :
    visible( false ),
    decimalDigits( KDCHART_DATA_VALUE_AUTO_DIGITS ),
    powerOfTenDivisor( 0 ),
    showInfinite( true )
{
    Measure me( 25.0,
                KDChartEnums::MeasureCalculationModeAuto,
                KDChartEnums::MeasureOrientationAuto );
    textAttributes.setFontSize( me );
    me.setValue( 8.0 );
    me.setCalculationMode( KDChartEnums::MeasureCalculationModeAbsolute );
    textAttributes.setMinimalFontSize( me );
    textAttributes.setRotation( -45 );

    // we set the Position to unknown: so the diagrams can take their own decisions
    positiveRelPos.setReferencePosition( Position::Unknown ); // a bar diagram will use: Position::NorthWest
    negativeRelPos.setReferencePosition( Position::Unknown ); // a bar diagram will use: Position::SouthEast

    positiveRelPos.setAlignment( Qt::AlignLeft  | Qt::AlignBottom );
    negativeRelPos.setAlignment( Qt::AlignRight | Qt::AlignTop );

    showRepetitiveDataLabels = false;
    showOverlappingDataLabels = false;

    // By default use 0.4 (or 0.5, resp.) of the font height as horizontal distance between
    // the data and their respective data value texts,
    // and use 0.75 as the vertical distance.
    const double posHoriPadding =  400.0; const double posVertPadding = -75.0;
    const double negHoriPadding = -500.0; const double negVertPadding =  75.0;
    Measure m( posHoriPadding, KDChartEnums::MeasureCalculationModeAuto );
    positiveRelPos.setHorizontalPadding( m );
    m.setValue( posVertPadding );
    positiveRelPos.setVerticalPadding( m );
    m.setValue( negHoriPadding );
    negativeRelPos.setHorizontalPadding( m );
    m.setValue( negVertPadding );
    negativeRelPos.setVerticalPadding( m );
}


DataValueAttributes::DataValueAttributes()
    : _d( new Private() )
{
}

DataValueAttributes::DataValueAttributes( const DataValueAttributes& r )
    : _d( new Private( *r.d ) )
{
}

DataValueAttributes & DataValueAttributes::operator=( const DataValueAttributes& r )
{
    if( this == &r )
        return *this;

    *d = *r.d;

    return *this;
}

DataValueAttributes::~DataValueAttributes()
{
    delete _d; _d = 0;
}


bool DataValueAttributes::operator==( const DataValueAttributes& r ) const
{
    /*
    qDebug() << "DataValueAttributes::operator== finds"
            << "b" << (isVisible() == r.isVisible())
            << "c" << (textAttributes() == r.textAttributes())
            << "d" << (frameAttributes() == r.frameAttributes())
            << "e" << (backgroundAttributes() == r.backgroundAttributes())
            << "f" << (markerAttributes() == r.markerAttributes())
            << "g" << (decimalDigits() == r.decimalDigits())
            << "h" << (prefix() == r.prefix())
            << "i" << (suffix() == r.suffix())
            << "j" << (dataLabel() == r.dataLabel())
            << "k" << (powerOfTenDivisor() == r.powerOfTenDivisor())
            << "l" << (showInfinite() == r.showInfinite())
            << "m" << (negativePosition() == r.negativePosition())
            << "n" << (positivePosition() == r.positivePosition())
            << "o" << (showRepetitiveDataLabels() == r.showRepetitiveDataLabels())
            << "p" << (showOverlappingDataLabels() == r.showOverlappingDataLabels());
    */
    return ( isVisible() == r.isVisible() &&
            textAttributes() == r.textAttributes() &&
            frameAttributes() == r.frameAttributes() &&
            backgroundAttributes() == r.backgroundAttributes() &&
            markerAttributes() == r.markerAttributes() &&
            decimalDigits() == r.decimalDigits() &&
            prefix() == r.prefix() &&
            suffix() == r.suffix() &&
            dataLabel() == r.dataLabel() &&
            powerOfTenDivisor() == r.powerOfTenDivisor() &&
            showInfinite() == r.showInfinite() &&
            negativePosition() == r.negativePosition() &&
            positivePosition() == r.positivePosition() &&
            showRepetitiveDataLabels() == r.showRepetitiveDataLabels() &&
            showOverlappingDataLabels() == r.showOverlappingDataLabels() );
}

/*static*/
const DataValueAttributes& DataValueAttributes::defaultAttributes()
{
    static const DataValueAttributes theDefaultDataValueAttributes;
    return theDefaultDataValueAttributes;
}

/*static*/
const QVariant& DataValueAttributes::defaultAttributesAsVariant()
{
    static const QVariant theDefaultDataValueAttributesVariant = qVariantFromValue(defaultAttributes());
    return theDefaultDataValueAttributesVariant;
}


void DataValueAttributes::setVisible( bool visible )
{
    d->visible = visible;
}

bool DataValueAttributes::isVisible() const
{
    return d->visible;
}

void DataValueAttributes::setTextAttributes( const TextAttributes &a )
{
    d->textAttributes = a;
}

TextAttributes DataValueAttributes::textAttributes() const
{
    return d->textAttributes;
}

void DataValueAttributes::setFrameAttributes( const FrameAttributes &a )
{
    d->frameAttributes = a;
}

FrameAttributes DataValueAttributes::frameAttributes() const
{
    return d->frameAttributes;
}

void DataValueAttributes::setBackgroundAttributes( const BackgroundAttributes &a )
{
    d->backgroundAttributes = a;
}

BackgroundAttributes DataValueAttributes::backgroundAttributes() const
{
    return d->backgroundAttributes;
}

void DataValueAttributes::setMarkerAttributes( const MarkerAttributes &a )
{
    d->markerAttributes = a;
}

MarkerAttributes DataValueAttributes::markerAttributes() const
{
    return d->markerAttributes;
}


void DataValueAttributes::setDecimalDigits( int digits )
{
    d->decimalDigits = digits;
}

int DataValueAttributes::decimalDigits() const
{
    return d->decimalDigits;
}

void DataValueAttributes::setPrefix( const QString prefixString )
{
    d->prefix = prefixString;
}

QString DataValueAttributes::prefix() const
{
    return d->prefix;
}

void DataValueAttributes::setSuffix( const QString suffixString )
{
    d->suffix  = suffixString;
}

QString DataValueAttributes::suffix() const
{
    return d->suffix;
}

void DataValueAttributes::setDataLabel( const QString label )
{
    d->dataLabel =  label;
}

QString DataValueAttributes::dataLabel() const
{
    return d->dataLabel;
}

bool DataValueAttributes::showRepetitiveDataLabels() const
{
    return d->showRepetitiveDataLabels;
}

void DataValueAttributes::setShowRepetitiveDataLabels( bool showRepetitiveDataLabels )
{
    d->showRepetitiveDataLabels = showRepetitiveDataLabels;
}

bool DataValueAttributes::showOverlappingDataLabels() const
{
    return d->showOverlappingDataLabels;
}

void DataValueAttributes::setShowOverlappingDataLabels( bool showOverlappingDataLabels )
{
    d->showOverlappingDataLabels = showOverlappingDataLabels;
}

void DataValueAttributes::setPowerOfTenDivisor( int powerOfTenDivisor )
{
    d->powerOfTenDivisor = powerOfTenDivisor;
}

int DataValueAttributes::powerOfTenDivisor() const
{
    return d->powerOfTenDivisor;
}

void DataValueAttributes::setShowInfinite( bool infinite )
{
    d->showInfinite = infinite;
}

bool DataValueAttributes::showInfinite() const
{
    return d->showInfinite;
}

void DataValueAttributes::setNegativePosition( const RelativePosition& relPosition )
{
    d->negativeRelPos = relPosition;
}

const RelativePosition DataValueAttributes::negativePosition() const
{
    return d->negativeRelPos;
}

void DataValueAttributes::setPositivePosition( const RelativePosition& relPosition )
{
    d->positiveRelPos = relPosition;
}

const RelativePosition DataValueAttributes::positivePosition() const
{
    return d->positiveRelPos;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KDChart::DataValueAttributes& val )
{
    dbg << "RelativePosition DataValueAttributes("
	<< "visible="<<val.isVisible()
	<< "textattributes="<<val.textAttributes()
	<< "frameattributes="<<val.frameAttributes()
	<< "backgroundattributes="<<val.backgroundAttributes()
	<< "decimaldigits="<<val.decimalDigits()
	<< "poweroftendivisor="<<val.powerOfTenDivisor()
	<< "showinfinite="<<val.showInfinite()
	<< "negativerelativeposition="<<val.negativePosition()
	<< "positiverelativeposition="<<val.positivePosition()
    << "showRepetitiveDataLabels="<<val.showRepetitiveDataLabels()
    << "showOverlappingDataLabels="<<val.showOverlappingDataLabels()
    <<")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
