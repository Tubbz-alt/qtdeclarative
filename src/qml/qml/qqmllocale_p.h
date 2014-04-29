/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQMLLOCALE_H
#define QQMLLOCALE_H

#include <qqml.h>

#include <QtCore/qlocale.h>
#include <QtCore/qobject.h>
#include <private/qv8engine_p.h>


QT_BEGIN_NAMESPACE


class QQmlDateExtension
{
public:
    static void registerExtension(QV4::ExecutionEngine *engine);

private:
    static QV4::ReturnedValue method_toLocaleString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_toLocaleTimeString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_toLocaleDateString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_fromLocaleString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_fromLocaleTimeString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_fromLocaleDateString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_timeZoneUpdated(QV4::CallContext *ctx);
};


class QQmlNumberExtension
{
public:
    static void registerExtension(QV4::ExecutionEngine *engine);

private:
    static QV4::ReturnedValue method_toLocaleString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_fromLocaleString(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_toLocaleCurrencyString(QV4::CallContext *ctx);
};


class Q_AUTOTEST_EXPORT QQmlLocale
{
    Q_GADGET
    Q_ENUMS(MeasurementSystem)
    Q_ENUMS(FormatType)
    Q_ENUMS(CurrencySymbolFormat)
    Q_ENUMS(DayOfWeek)

public:
    ~QQmlLocale();

    enum MeasurementSystem {
        MetricSystem = QLocale::MetricSystem,
        ImperialSystem = QLocale::ImperialSystem,
        ImperialUSSystem = QLocale::ImperialUSSystem,
        ImperialUKSystem = QLocale::ImperialUKSystem
    };
    enum FormatType {
        LongFormat = QLocale::LongFormat,
        ShortFormat = QLocale::ShortFormat,
        NarrowFormat = QLocale::NarrowFormat
    };
    enum CurrencySymbolFormat {
        CurrencyIsoCode = QLocale::CurrencyIsoCode,
        CurrencySymbol = QLocale::CurrencySymbol,
        CurrencyDisplayName = QLocale::CurrencyDisplayName
    };
    // Qt defines Sunday as 7, but JS Date assigns Sunday 0
    enum DayOfWeek {
        Sunday = 0,
        Monday = Qt::Monday,
        Tuesday = Qt::Tuesday,
        Wednesday = Qt::Wednesday,
        Thursday = Qt::Thursday,
        Friday = Qt::Friday,
        Saturday = Qt::Saturday
    };

    static QV4::ReturnedValue locale(QV8Engine *v8engine, const QString &localeName);
    static QV4::ReturnedValue wrap(QV8Engine *engine, const QLocale &locale);

    static void registerStringLocaleCompare(QV4::ExecutionEngine *engine);

private:
    QQmlLocale();

    static QV4::ReturnedValue method_localeCompare(QV4::CallContext *ctx);
};

class QQmlLocaleData : public QV4::Object
{
    struct Data : QV4::Object::Data {
        QLocale locale;
    };
    struct {
        QLocale locale;
    } __data;

    V4_OBJECT_NEW
public:
    QQmlLocaleData(QV4::ExecutionEngine *engine)
        : QV4::Object(engine)
    {
        setVTable(staticVTable());
    }


    static QLocale *getThisLocale(QV4::CallContext *ctx) {
        QQmlLocaleData *thisObject = ctx->callData->thisObject.asObject()->as<QQmlLocaleData>();
        if (!thisObject) {
            ctx->throwTypeError();
            return 0;
        }
        return &thisObject->d()->locale;
    }

    static QV4::ReturnedValue method_currencySymbol(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_dateTimeFormat(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_timeFormat(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_dateFormat(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_monthName(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_standaloneMonthName(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_dayName(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_standaloneDayName(QV4::CallContext *ctx);

    static QV4::ReturnedValue method_get_firstDayOfWeek(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_measurementSystem(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_textDirection(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_weekDays(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_uiLanguages(QV4::CallContext *ctx);

    static QV4::ReturnedValue method_get_name(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_nativeLanguageName(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_nativeCountryName(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_decimalPoint(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_groupSeparator(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_percent(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_zeroDigit(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_negativeSign(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_positiveSign(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_exponential(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_amText(QV4::CallContext *ctx);
    static QV4::ReturnedValue method_get_pmText(QV4::CallContext *ctx);

private:
    static void destroy(Managed *that)
    {
        static_cast<QQmlLocaleData *>(that)->~QQmlLocaleData();
    }
};

QT_END_NAMESPACE

#endif
