/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <qtest.h>
#include <QSignalSpy>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/5.0.0/QtWidgets/private/qgraphicsitem_p.h>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativecomponent.h>
#include <QtQuick1/qdeclarativeview.h>
#include <QtQuick1/private/qdeclarativerectangle_p.h>
#include <QtQuick1/private/qdeclarativetext_p.h>
#include <QtQuick1/private/qdeclarativeanchors_p_p.h>
#include <QtQuick1/private/qdeclarativeitem_p.h>

Q_DECLARE_METATYPE(QDeclarative1Anchors::Anchor)
Q_DECLARE_METATYPE(QDeclarative1AnchorLine::AnchorLine)

class tst_QDeclarative1Anchors : public QObject
{
    Q_OBJECT
public:
    tst_QDeclarative1Anchors() {}

private slots:
    void basicAnchors();
    void basicAnchorsQGraphicsWidget();
    void basicAnchorsRTL();
    void loops();
    void illegalSets();
    void illegalSets_data();
    void reset();
    void reset_data();
    void resetConvenience();
    void nullItem();
    void nullItem_data();
    void crash1();
    void centerIn();
    void centerInRTL();
    void hvCenter();
    void hvCenterRTL();
    void fill();
    void fillRTL();
    void margins();
    void marginsRTL();
};

/*
   Find an item with the specified id.
*/
template<typename T>
T *findItem(QGraphicsObject *parent, const QString &objectName)
{
    const QMetaObject &mo = T::staticMetaObject;
    QList<QGraphicsItem *> children = parent->childItems();
    for (int i = 0; i < children.count(); ++i) {
        QDeclarativeItem *item = qobject_cast<QDeclarativeItem *>(children.at(i)->toGraphicsObject());
        if (item) {
            if (mo.cast(item) && (objectName.isEmpty() || item->objectName() == objectName)) {
                return static_cast<T*>(item);
            }
            item = findItem<T>(item, objectName);
            if (item)
                return static_cast<T*>(item);
        }
    }

    return 0;
}

QGraphicsObject *findObject(QGraphicsObject *parent, const QString &objectName)
{
    QList<QGraphicsItem *> children = parent->childItems();
    for (int i = 0; i < children.count(); ++i) {
        QGraphicsObject *item = children.at(i)->toGraphicsObject();
        if (item) {
            if (objectName.isEmpty() || item->objectName() == objectName) {
                return item;
            }
            item = findObject(item, objectName);
            if (item)
                return item;
        }
    }

    return 0;
}


void tst_QDeclarative1Anchors::basicAnchors()
{
    QDeclarativeView *view = new QDeclarativeView;
    view->setSource(QUrl::fromLocalFile(SRCDIR "/data/anchors.qml"));

    qApp->processEvents();

    //sibling horizontal
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect1"))->x(), 26.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect2"))->x(), 122.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect3"))->x(), 74.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect4"))->x(), 16.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect5"))->x(), 112.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect6"))->x(), 64.0);

    //parent horizontal
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect7"))->x(), 0.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect8"))->x(), 240.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect9"))->x(), 120.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect10"))->x(), -10.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect11"))->x(), 230.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect12"))->x(), 110.0);

    //vertical
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect13"))->y(), 20.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect14"))->y(), 155.0);

    //stretch
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect15"))->x(), 26.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect15"))->width(), 96.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect16"))->x(), 26.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect16"))->width(), 192.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect17"))->x(), -70.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect17"))->width(), 192.0);

    //vertical stretch
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect18"))->y(), 20.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect18"))->height(), 40.0);

    //more parent horizontal
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect19"))->x(), 115.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect20"))->x(), 235.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect21"))->x(), -5.0);

    //centerIn
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect22"))->x(), 69.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect22"))->y(), 5.0);

     //margins
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect23"))->x(), 31.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect23"))->y(), 5.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect23"))->width(), 86.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect23"))->height(), 10.0);

    // offsets
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect24"))->x(), 26.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect25"))->y(), 60.0);
    QCOMPARE(findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("rect26"))->y(), 5.0);

    //baseline
    QDeclarative1Text *text1 = findItem<QDeclarative1Text>(view->rootObject(), QLatin1String("text1"));
    QDeclarative1Text *text2 = findItem<QDeclarative1Text>(view->rootObject(), QLatin1String("text2"));
    QCOMPARE(text1->y(), text2->y());

    delete view;
}

void tst_QDeclarative1Anchors::basicAnchorsQGraphicsWidget()
{
    QDeclarativeView *view = new QDeclarativeView;
    view->setSource(QUrl::fromLocalFile(SRCDIR "/data/anchorsqgraphicswidget.qml"));

    qApp->processEvents();

    //sibling horizontal
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect1"))->x(), 26.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect2"))->x(), 122.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect3"))->x(), 74.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect4"))->x(), 16.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect5"))->x(), 112.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect6"))->x(), 64.0);

    //parent horizontal
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect7"))->x(), 0.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect8"))->x(), 240.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect9"))->x(), 120.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect10"))->x(), -10.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect11"))->x(), 230.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect12"))->x(), 110.0);

    //vertical
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect13"))->y(), 20.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect14"))->y(), 155.0);

    //stretch
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect15"))->x(), 26.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect15"))->property("width").toReal(), 96.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect16"))->x(), 26.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect16"))->property("width").toReal(), 192.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect17"))->x(), -70.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect17"))->property("width").toReal(), 192.0);

    //vertical stretch
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect18"))->y(), 20.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect18"))->property("height").toReal(), 40.0);

    //more parent horizontal
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect19"))->x(), 115.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect20"))->x(), 235.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect21"))->x(), -5.0);

    //centerIn
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect22"))->x(), 69.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect22"))->y(), 5.0);

     //margins
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect23"))->x(), 31.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect23"))->y(), 5.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect23"))->property("width").toReal(), 86.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect23"))->property("height").toReal(), 10.0);

    // offsets
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect24"))->x(), 26.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect25"))->y(), 60.0);
    QCOMPARE(findObject(view->rootObject(), QLatin1String("rect26"))->y(), 5.0);

    //baseline
    QDeclarative1Text *text1 = findItem<QDeclarative1Text>(view->rootObject(), QLatin1String("text1"));
    QDeclarative1Text *text2 = findItem<QDeclarative1Text>(view->rootObject(), QLatin1String("text2"));
    QCOMPARE(text1->y(), text2->y());

    delete view;
}

QDeclarativeItem* childItem(QDeclarativeItem *parentItem, const char * itemString) {
    return findItem<QDeclarativeItem>(parentItem, QLatin1String(itemString));
}

qreal offsetMasterRTL(QDeclarativeItem *rootItem, const char * itemString) {
    QDeclarativeItem* masterItem = findItem<QDeclarativeItem>(rootItem,  QLatin1String("masterRect"));
    return masterItem->width()+2*masterItem->x()-findItem<QDeclarativeItem>(rootItem,  QLatin1String(itemString))->width();
}

qreal offsetParentRTL(QDeclarativeItem *rootItem, const char * itemString) {
    return rootItem->width()+2*rootItem->x()-findItem<QDeclarativeItem>(rootItem,  QLatin1String(itemString))->width();
}

void mirrorAnchors(QDeclarativeItem *item) {
    QDeclarativeItemPrivate *itemPrivate = QDeclarativeItemPrivate::get(item);
    itemPrivate->setLayoutMirror(true);
}

void tst_QDeclarative1Anchors::basicAnchorsRTL()
{
    QDeclarativeView *view = new QDeclarativeView;
    view->setSource(QUrl::fromLocalFile(SRCDIR "/data/anchors.qml"));

    qApp->processEvents();

    QDeclarativeItem* rootItem = qobject_cast<QDeclarativeItem*>(view->rootObject());
    foreach(QObject *child, rootItem->children()) {
        bool mirrored = QDeclarativeItemPrivate::get(qobject_cast<QDeclarativeItem*>(child))->anchors()->property("mirrored").toBool();
        QCOMPARE(mirrored, false);
    }

    foreach(QObject *child, rootItem->children())
        mirrorAnchors(qobject_cast<QDeclarativeItem*>(child));

    foreach(QObject *child, rootItem->children()) {
        bool mirrored = QDeclarativeItemPrivate::get(qobject_cast<QDeclarativeItem*>(child))->anchors()->property("mirrored").toBool();
        QCOMPARE(mirrored, true);
    }

    //sibling horizontal
    QCOMPARE(childItem(rootItem, "rect1")->x(), offsetMasterRTL(rootItem, "rect1")-26.0);
    QCOMPARE(childItem(rootItem, "rect2")->x(), offsetMasterRTL(rootItem, "rect2")-122.0);
    QCOMPARE(childItem(rootItem, "rect3")->x(), offsetMasterRTL(rootItem, "rect3")-74.0);
    QCOMPARE(childItem(rootItem, "rect4")->x(), offsetMasterRTL(rootItem, "rect4")-16.0);
    QCOMPARE(childItem(rootItem, "rect5")->x(), offsetMasterRTL(rootItem, "rect5")-112.0);
    QCOMPARE(childItem(rootItem, "rect6")->x(), offsetMasterRTL(rootItem, "rect6")-64.0);

    //parent horizontal
    QCOMPARE(childItem(rootItem, "rect7")->x(), offsetParentRTL(rootItem, "rect7")-0.0);
    QCOMPARE(childItem(rootItem, "rect8")->x(), offsetParentRTL(rootItem, "rect8")-240.0);
    QCOMPARE(childItem(rootItem, "rect9")->x(), offsetParentRTL(rootItem, "rect9")-120.0);
    QCOMPARE(childItem(rootItem, "rect10")->x(), offsetParentRTL(rootItem, "rect10")+10.0);
    QCOMPARE(childItem(rootItem, "rect11")->x(), offsetParentRTL(rootItem, "rect11")-230.0);
    QCOMPARE(childItem(rootItem, "rect12")->x(), offsetParentRTL(rootItem, "rect12")-110.0);

    //vertical
    QCOMPARE(childItem(rootItem, "rect13")->y(), 20.0);
    QCOMPARE(childItem(rootItem, "rect14")->y(), 155.0);

    //stretch
    QCOMPARE(childItem(rootItem, "rect15")->x(), offsetMasterRTL(rootItem, "rect15")-26.0);
    QCOMPARE(childItem(rootItem, "rect15")->width(), 96.0);
    QCOMPARE(childItem(rootItem, "rect16")->x(), offsetMasterRTL(rootItem, "rect16")-26.0);
    QCOMPARE(childItem(rootItem, "rect16")->width(), 192.0);
    QCOMPARE(childItem(rootItem, "rect17")->x(), offsetMasterRTL(rootItem, "rect17")+70.0);
    QCOMPARE(childItem(rootItem, "rect17")->width(), 192.0);

    //vertical stretch
    QCOMPARE(childItem(rootItem, "rect18")->y(), 20.0);
    QCOMPARE(childItem(rootItem, "rect18")->height(), 40.0);

    //more parent horizontal
    QCOMPARE(childItem(rootItem, "rect19")->x(), offsetParentRTL(rootItem, "rect19")-115.0);
    QCOMPARE(childItem(rootItem, "rect20")->x(), offsetParentRTL(rootItem, "rect20")-235.0);
    QCOMPARE(childItem(rootItem, "rect21")->x(), offsetParentRTL(rootItem, "rect21")+5.0);

    //centerIn
    QCOMPARE(childItem(rootItem, "rect22")->x(), offsetMasterRTL(rootItem, "rect22")-69.0);
    QCOMPARE(childItem(rootItem, "rect22")->y(), 5.0);

     //margins
    QCOMPARE(childItem(rootItem, "rect23")->x(), offsetMasterRTL(rootItem, "rect23")-31.0);
    QCOMPARE(childItem(rootItem, "rect23")->y(), 5.0);
    QCOMPARE(childItem(rootItem, "rect23")->width(), 86.0);
    QCOMPARE(childItem(rootItem, "rect23")->height(), 10.0);

    // offsets
    QCOMPARE(childItem(rootItem, "rect24")->x(), offsetMasterRTL(rootItem, "rect24")-26.0);
    QCOMPARE(childItem(rootItem, "rect25")->y(), 60.0);
    QCOMPARE(childItem(rootItem, "rect26")->y(), 5.0);

    //baseline
    QDeclarative1Text *text1 = findItem<QDeclarative1Text>(rootItem, QLatin1String("text1"));
    QDeclarative1Text *text2 = findItem<QDeclarative1Text>(rootItem, QLatin1String("text2"));
    QCOMPARE(text1->y(), text2->y());

    delete view;
}

// mostly testing that we don't crash
void tst_QDeclarative1Anchors::loops()
{
    {
        QUrl source(QUrl::fromLocalFile(SRCDIR "/data/loop1.qml"));

        QString expect = source.toString() + ":6:5: QML Text: Possible anchor loop detected on horizontal anchor.";
        QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
        QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
        QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());

        QDeclarativeView *view = new QDeclarativeView;
        view->setSource(source);
        qApp->processEvents();

        delete view;
    }

    {
        QSKIP("This causes a lockup due to Bearer management stuff", SkipSingle);
        QUrl source(QUrl::fromLocalFile(SRCDIR "/data/loop2.qml"));

        QString expect = source.toString() + ":8:3: QML Image: Possible anchor loop detected on horizontal anchor.";
        QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());

        QDeclarativeView *view = new QDeclarativeView;
        view->setSource(source);
        qApp->processEvents();

        delete view;
    }
}

void tst_QDeclarative1Anchors::illegalSets()
{
    QFETCH(QString, qml);
    QFETCH(QString, warning);

    QTest::ignoreMessage(QtWarningMsg, warning.toLatin1());

    QDeclarativeEngine engine;
    QDeclarativeComponent component(&engine);
    component.setData(QByteArray("import QtQuick 1.0\n" + qml.toUtf8()), QUrl::fromLocalFile(""));
    if (!component.isReady())
        qWarning() << "Test errors:" << component.errors();
    QVERIFY(component.isReady());
    QObject *o = component.create();
    delete o;
}

void tst_QDeclarative1Anchors::illegalSets_data()
{
    QTest::addColumn<QString>("qml");
    QTest::addColumn<QString>("warning");

    QTest::newRow("H - too many anchors")
        << "Rectangle { id: rect; Rectangle { anchors.left: rect.left; anchors.right: rect.right; anchors.horizontalCenter: rect.horizontalCenter } }"
        << "file::2:23: QML Rectangle: Cannot specify left, right, and hcenter anchors.";

    foreach (const QString &side, QStringList() << "left" << "right") {
        QTest::newRow("H - anchor to V")
            << QString("Rectangle { Rectangle { anchors.%1: parent.top } }").arg(side)
            << "file::2:13: QML Rectangle: Cannot anchor a horizontal edge to a vertical edge.";

        QTest::newRow("H - anchor to non parent/sibling")
            << QString("Rectangle { Item { Rectangle { id: rect } } Rectangle { anchors.%1: rect.%1 } }").arg(side)
            << "file::2:45: QML Rectangle: Cannot anchor to an item that isn't a parent or sibling.";

        QTest::newRow("H - anchor to self")
            << QString("Rectangle { id: rect; anchors.%1: rect.%1 }").arg(side)
            << "file::2:1: QML Rectangle: Cannot anchor item to self.";
    }


    QTest::newRow("V - too many anchors")
        << "Rectangle { id: rect; Rectangle { anchors.top: rect.top; anchors.bottom: rect.bottom; anchors.verticalCenter: rect.verticalCenter } }"
        << "file::2:23: QML Rectangle: Cannot specify top, bottom, and vcenter anchors.";

    QTest::newRow("V - too many anchors with baseline")
        << "Rectangle { Text { id: text1; text: \"Hello\" } Text { anchors.baseline: text1.baseline; anchors.top: text1.top; } }"
        << "file::2:47: QML Text: Baseline anchor cannot be used in conjunction with top, bottom, or vcenter anchors.";

    foreach (const QString &side, QStringList() << "top" << "bottom" << "baseline") {

        QTest::newRow("V - anchor to H")
            << QString("Rectangle { Rectangle { anchors.%1: parent.left } }").arg(side)
            << "file::2:13: QML Rectangle: Cannot anchor a vertical edge to a horizontal edge.";

        QTest::newRow("V - anchor to non parent/sibling")
            << QString("Rectangle { Item { Rectangle { id: rect } } Rectangle { anchors.%1: rect.%1 } }").arg(side)
            << "file::2:45: QML Rectangle: Cannot anchor to an item that isn't a parent or sibling.";

        QTest::newRow("V - anchor to self")
            << QString("Rectangle { id: rect; anchors.%1: rect.%1 }").arg(side)
            << "file::2:1: QML Rectangle: Cannot anchor item to self.";
    }


    QTest::newRow("centerIn - anchor to non parent/sibling")
        << "Rectangle { Item { Rectangle { id: rect } } Rectangle { anchors.centerIn: rect} }"
        << "file::2:45: QML Rectangle: Cannot anchor to an item that isn't a parent or sibling.";


    QTest::newRow("fill - anchor to non parent/sibling")
        << "Rectangle { Item { Rectangle { id: rect } } Rectangle { anchors.fill: rect} }"
        << "file::2:45: QML Rectangle: Cannot anchor to an item that isn't a parent or sibling.";
}

void tst_QDeclarative1Anchors::reset()
{
    QFETCH(QString, side);
    QFETCH(QDeclarative1AnchorLine::AnchorLine, anchorLine);
    QFETCH(QDeclarative1Anchors::Anchor, usedAnchor);

    QDeclarativeItem *baseItem = new QDeclarativeItem;

    QDeclarative1AnchorLine anchor;
    anchor.item = baseItem;
    anchor.anchorLine = anchorLine;

    QDeclarativeItem *item = new QDeclarativeItem;
    QDeclarativeItemPrivate *itemPrivate = QDeclarativeItemPrivate::get(item);

    const QMetaObject *meta = itemPrivate->anchors()->metaObject();
    QMetaProperty p = meta->property(meta->indexOfProperty(side.toUtf8().constData()));

    QVERIFY(p.write(itemPrivate->anchors(), qVariantFromValue(anchor)));
    QCOMPARE(itemPrivate->anchors()->usedAnchors().testFlag(usedAnchor), true);

    QVERIFY(p.reset(itemPrivate->anchors()));
    QCOMPARE(itemPrivate->anchors()->usedAnchors().testFlag(usedAnchor), false);

    delete item;
    delete baseItem;
}

void tst_QDeclarative1Anchors::reset_data()
{
    QTest::addColumn<QString>("side");
    QTest::addColumn<QDeclarative1AnchorLine::AnchorLine>("anchorLine");
    QTest::addColumn<QDeclarative1Anchors::Anchor>("usedAnchor");

    QTest::newRow("left") << "left" << QDeclarative1AnchorLine::Left << QDeclarative1Anchors::LeftAnchor;
    QTest::newRow("top") << "top" << QDeclarative1AnchorLine::Top << QDeclarative1Anchors::TopAnchor;
    QTest::newRow("right") << "right" << QDeclarative1AnchorLine::Right << QDeclarative1Anchors::RightAnchor;
    QTest::newRow("bottom") << "bottom" << QDeclarative1AnchorLine::Bottom << QDeclarative1Anchors::BottomAnchor;

    QTest::newRow("hcenter") << "horizontalCenter" << QDeclarative1AnchorLine::HCenter << QDeclarative1Anchors::HCenterAnchor;
    QTest::newRow("vcenter") << "verticalCenter" << QDeclarative1AnchorLine::VCenter << QDeclarative1Anchors::VCenterAnchor;
    QTest::newRow("baseline") << "baseline" << QDeclarative1AnchorLine::Baseline << QDeclarative1Anchors::BaselineAnchor;
}

void tst_QDeclarative1Anchors::resetConvenience()
{
    QDeclarativeItem *baseItem = new QDeclarativeItem;
    QDeclarativeItem *item = new QDeclarativeItem;
    QDeclarativeItemPrivate *itemPrivate = QDeclarativeItemPrivate::get(item);

    //fill
    itemPrivate->anchors()->setFill(baseItem);
    QVERIFY(itemPrivate->anchors()->fill() == baseItem);
    itemPrivate->anchors()->resetFill();
    QVERIFY(itemPrivate->anchors()->fill() == 0);

    //centerIn
    itemPrivate->anchors()->setCenterIn(baseItem);
    QVERIFY(itemPrivate->anchors()->centerIn() == baseItem);
    itemPrivate->anchors()->resetCenterIn();
    QVERIFY(itemPrivate->anchors()->centerIn() == 0);

    delete item;
    delete baseItem;
}

void tst_QDeclarative1Anchors::nullItem()
{
    QFETCH(QString, side);

    QDeclarative1AnchorLine anchor;
    QDeclarativeItem *item = new QDeclarativeItem;
    QDeclarativeItemPrivate *itemPrivate = QDeclarativeItemPrivate::get(item);

    const QMetaObject *meta = itemPrivate->anchors()->metaObject();
    QMetaProperty p = meta->property(meta->indexOfProperty(side.toUtf8().constData()));

    QTest::ignoreMessage(QtWarningMsg, "<Unknown File>: QML Item: Cannot anchor to a null item.");
    QVERIFY(p.write(itemPrivate->anchors(), qVariantFromValue(anchor)));

    delete item;
}

void tst_QDeclarative1Anchors::nullItem_data()
{
    QTest::addColumn<QString>("side");

    QTest::newRow("left") << "left";
    QTest::newRow("top") << "top";
    QTest::newRow("right") << "right";
    QTest::newRow("bottom") << "bottom";

    QTest::newRow("hcenter") << "horizontalCenter";
    QTest::newRow("vcenter") << "verticalCenter";
    QTest::newRow("baseline") << "baseline";
}

void tst_QDeclarative1Anchors::crash1()
{
    QUrl source(QUrl::fromLocalFile(SRCDIR "/data/crash1.qml"));

    QString expect = source.toString() + ":4:5: QML Text: Possible anchor loop detected on fill.";

    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());

    // QT-3245 ... anchor loop detection needs improving.
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());
    QTest::ignoreMessage(QtWarningMsg, expect.toLatin1());

    QDeclarativeView *view = new QDeclarativeView(source);
    qApp->processEvents();

    delete view;
}

void tst_QDeclarative1Anchors::fill()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/fill.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("filler"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);
    QCOMPARE(rect->x(), 0.0 + 10.0);
    QCOMPARE(rect->y(), 0.0 + 30.0);
    QCOMPARE(rect->width(), 200.0 - 10.0 - 20.0);
    QCOMPARE(rect->height(), 200.0 - 30.0 - 40.0);
    //Alter Offsets (tests QTBUG-6631)
    rectPrivate->anchors()->setLeftMargin(20.0);
    rectPrivate->anchors()->setRightMargin(0.0);
    rectPrivate->anchors()->setBottomMargin(0.0);
    rectPrivate->anchors()->setTopMargin(10.0);
    QCOMPARE(rect->x(), 0.0 + 20.0);
    QCOMPARE(rect->y(), 0.0 + 10.0);
    QCOMPARE(rect->width(), 200.0 - 20.0);
    QCOMPARE(rect->height(), 200.0 - 10.0);

    delete view;
}

void tst_QDeclarative1Anchors::fillRTL()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/fill.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("filler"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);
    mirrorAnchors(rect);

    QCOMPARE(rect->x(), 0.0 + 20.0);
    QCOMPARE(rect->y(), 0.0 + 30.0);
    QCOMPARE(rect->width(), 200.0 - 10.0 - 20.0);
    QCOMPARE(rect->height(), 200.0 - 30.0 - 40.0);
    //Alter Offsets (tests QTBUG-6631)
    rectPrivate->anchors()->setLeftMargin(20.0);
    rectPrivate->anchors()->setRightMargin(0.0);
    rectPrivate->anchors()->setBottomMargin(0.0);
    rectPrivate->anchors()->setTopMargin(10.0);
    QCOMPARE(rect->x(), 0.0 + 0.0);
    QCOMPARE(rect->y(), 0.0 + 10.0);
    QCOMPARE(rect->width(), 200.0 - 20.0);
    QCOMPARE(rect->height(), 200.0 - 10.0);

    delete view;
}
void tst_QDeclarative1Anchors::centerIn()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/centerin.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("centered"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);

    QCOMPARE(rect->x(), 75.0 + 10);
    QCOMPARE(rect->y(), 75.0 + 30);
    //Alter Offsets (tests QTBUG-6631)
    rectPrivate->anchors()->setHorizontalCenterOffset(-20.0);
    rectPrivate->anchors()->setVerticalCenterOffset(-10.0);
    QCOMPARE(rect->x(), 75.0 - 20.0);
    QCOMPARE(rect->y(), 75.0 - 10.0);

    delete view;
}


void tst_QDeclarative1Anchors::centerInRTL()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/centerin.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("centered"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);
    mirrorAnchors(rect);

    QCOMPARE(rect->x(), 75.0 - 10);
    QCOMPARE(rect->y(), 75.0 + 30);
    //Alter Offsets (tests QTBUG-6631)
    rectPrivate->anchors()->setHorizontalCenterOffset(-20.0);
    rectPrivate->anchors()->setVerticalCenterOffset(-10.0);
    QCOMPARE(rect->x(), 75.0 + 20.0);
    QCOMPARE(rect->y(), 75.0 - 10.0);

    delete view;
}

void tst_QDeclarative1Anchors::hvCenter()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/hvCenter.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("centered"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);

    // test QTBUG-10999
    QCOMPARE(rect->x(), 10.0);
    QCOMPARE(rect->y(), 19.0);

    rectPrivate->anchors()->setHorizontalCenterOffset(-5.0);
    rectPrivate->anchors()->setVerticalCenterOffset(5.0);
    QCOMPARE(rect->x(), 10.0 - 5.0);
    QCOMPARE(rect->y(), 19.0 + 5.0);

    delete view;
}

void tst_QDeclarative1Anchors::hvCenterRTL()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/hvCenter.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("centered"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);
    mirrorAnchors(rect);

    // test QTBUG-10999
    QCOMPARE(rect->x(), 10.0);
    QCOMPARE(rect->y(), 19.0);

    rectPrivate->anchors()->setHorizontalCenterOffset(-5.0);
    rectPrivate->anchors()->setVerticalCenterOffset(5.0);
    QCOMPARE(rect->x(), 10.0 + 5.0);
    QCOMPARE(rect->y(), 19.0 + 5.0);

    delete view;
}
void tst_QDeclarative1Anchors::margins()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/margins.qml"));

    qApp->processEvents();
    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("filler"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);
    QCOMPARE(rect->x(), 5.0);
    QCOMPARE(rect->y(), 6.0);
    QCOMPARE(rect->width(), 200.0 - 5.0 - 10.0);
    QCOMPARE(rect->height(), 200.0 - 6.0 - 10.0);

    rectPrivate->anchors()->setTopMargin(0.0);
    rectPrivate->anchors()->setMargins(20.0);

    QCOMPARE(rect->x(), 5.0);
    QCOMPARE(rect->y(), 20.0);
    QCOMPARE(rect->width(), 200.0 - 5.0 - 20.0);
    QCOMPARE(rect->height(), 200.0 - 20.0 - 20.0);

    delete view;
}

void tst_QDeclarative1Anchors::marginsRTL()
{
    QDeclarativeView *view = new QDeclarativeView(QUrl::fromLocalFile(SRCDIR "/data/margins.qml"));

    QDeclarative1Rectangle* rect = findItem<QDeclarative1Rectangle>(view->rootObject(), QLatin1String("filler"));
    QDeclarativeItemPrivate *rectPrivate = QDeclarativeItemPrivate::get(rect);
    mirrorAnchors(rect);

    QCOMPARE(rect->x(), 10.0);
    QCOMPARE(rect->y(), 6.0);
    QCOMPARE(rect->width(), 200.0 - 5.0 - 10.0);
    QCOMPARE(rect->height(), 200.0 - 6.0 - 10.0);

    rectPrivate->anchors()->setTopMargin(0.0);
    rectPrivate->anchors()->setMargins(20.0);

    QCOMPARE(rect->x(), 20.0);
    QCOMPARE(rect->y(), 20.0);
    QCOMPARE(rect->width(), 200.0 - 5.0 - 20.0);
    QCOMPARE(rect->height(), 200.0 - 20.0 - 20.0);

    delete view;
}


QTEST_MAIN(tst_QDeclarative1Anchors)

#include "tst_qdeclarativeanchors.moc"
