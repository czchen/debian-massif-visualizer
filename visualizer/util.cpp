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

#include "util.h"

#include "massifdata/snapshotitem.h"
#include "massifdata/treeleafitem.h"

#include <KGlobal>
#include <KLocale>
#include <KConfigGroup>
#include <KDebug>

#include <QTextDocument>

namespace Massif {

QString prettyCost(unsigned long cost)
{
    Q_ASSERT(KGlobal::config());
    KConfigGroup conf = KGlobal::config()->group(QLatin1String("Settings"));
    int precision = conf.readEntry(QLatin1String("prettyCostPrecision"), 1);
    return KGlobal::locale()->formatByteSize(cost, precision);
}

QString prettyLabel(const QString& label)
{
    QString ret;

    int colonPos = label.indexOf(": ");
    if (colonPos == -1) {
        ret = label;
    } else {
        ret = label.mid(colonPos + 2);
    }

    Q_ASSERT(KGlobal::config());
    KConfigGroup conf = KGlobal::config()->group(QLatin1String("Settings"));
    if (conf.readEntry(QLatin1String("shortenTemplates"), false)) {
        // remove template arguments between <...>
        int depth = 0;
        int open = 0;
        for (int i = 0; i < ret.length(); ++i) {
            if (ret.at(i) == '<') {
                if (!depth) {
                    open = i;
                }
                ++depth;
            } else if (ret.at(i) == '>') {
                --depth;
                if (!depth) {
                    ret.remove(open + 1, i - open - 1);
                    i = open + 1;
                    open = 0;
                }
            }
        }
    }

    return ret;
}

QString functionInLabel(const QString& label)
{
    QString ret = prettyLabel(label);
    int pos = ret.lastIndexOf(" (");
    if (pos != -1) {
        ret.resize(pos);
    }
    return ret;
}

bool isBelowThreshold(const QString& label)
{
    return label.indexOf("all below massif's threshold") != -1;
}

QString formatLabel(const QString& label)
{
    static QRegExp pattern("^(0x.+: )?([^\\)]+\\))(?: \\(([^\\)]+)\\))?$", Qt::CaseSensitive,
                           QRegExp::RegExp2);
    pattern.setMinimal(true);
    if (pattern.indexIn(label) != -1) {
        QString ret;
        if (!pattern.cap(2).isEmpty()) {
            ret += i18n("<dt>function:</dt><dd>%1</dd>\n", Qt::escape(pattern.cap(2)));
        }
        if (!pattern.cap(3).isEmpty()) {
            ret += i18n("<dt>location:</dt><dd>%1</dd>\n", Qt::escape(pattern.cap(3)));
        }
        if (!pattern.cap(1).isEmpty()) {
            ret += i18n("<dt>address:</dt><dd>%1</dd>\n", Qt::escape(pattern.cap(1)));
        }
        return ret;
    } else {
        return label;
    }
}

QString tooltipForTreeLeaf(TreeLeafItem* node, SnapshotItem* snapshot, const QString& label)
{
    QString tooltip = "<html><head><style>dt{font-weight:bold;} dd {font-family:monospace;}</style></head><body><dl>\n";
    tooltip += i18n("<dt>cost:</dt><dd>%1, i.e. %2% of snapshot #%3</dd>", prettyCost(node ? node->cost() : 0),
                    // yeah nice how I round to two decimals, right? :D
                    double(int(double(node ? node->cost() : 0)/snapshot->memHeap()*10000))/100, snapshot->number());
    tooltip += formatLabel(label);
    tooltip += "</dl></body></html>";
    return tooltip;
}

}
