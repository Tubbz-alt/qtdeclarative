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
#include <QtTest/QtTest>
#include <private/qlistmodelinterface_p.h>
#include <qsgview.h>
#include <qdeclarativeengine.h>
#include <private/qsgrectangle_p.h>
#include <private/qsgpositioners_p.h>
#include <private/qdeclarativetransition_p.h>
#include <private/qsgitem_p.h>
#include <qdeclarativeexpression.h>
#include <QtWidgets/qgraphicswidget.h>
#include "../../../shared/util.h"

class tst_qsgpositioners : public QObject
{
    Q_OBJECT
public:
    tst_qsgpositioners();

private slots:
    void test_horizontal();
    void test_horizontal_rtl();
    void test_horizontal_spacing();
    void test_horizontal_spacing_rightToLeft();
    void test_horizontal_animated();
    void test_horizontal_animated_rightToLeft();
    void test_horizontal_animated_disabled();
    void test_vertical();
    void test_vertical_spacing();
    void test_vertical_animated();
    void test_grid();
    void test_grid_topToBottom();
    void test_grid_rightToLeft();
    void test_grid_spacing();
    void test_grid_row_column_spacing();
    void test_grid_animated();
    void test_grid_animated_rightToLeft();
    void test_grid_zero_columns();
    void test_propertychanges();
    void test_repeater();
    void test_flow();
    void test_flow_rightToLeft();
    void test_flow_topToBottom();
    void test_flow_resize();
    void test_flow_resize_rightToLeft();
    void test_flow_implicit_resize();
    void test_conflictinganchors();
    void test_mirroring();
    void test_allInvisible();
    void test_attachedproperties();
    void test_attachedproperties_data();
    void test_attachedproperties_dynamic();

private:
    QSGView *createView(const QString &filename, bool wait=true);
};

tst_qsgpositioners::tst_qsgpositioners()
{
}

void tst_qsgpositioners::test_horizontal()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal.qml");

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 70.0);
    QCOMPARE(three->y(), 0.0);

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QCOMPARE(row->width(), 110.0);
    QCOMPARE(row->height(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_horizontal_rtl()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal.qml");

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 60.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 40.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 0.0);

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QCOMPARE(row->width(), 110.0);
    QCOMPARE(row->height(), 50.0);

    // Change the width of the row and check that items stay to the right
    row->setWidth(200);
    QTRY_COMPARE(one->x(), 150.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 130.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 90.0);
    QCOMPARE(three->y(), 0.0);

    delete canvas;
}

void tst_qsgpositioners::test_horizontal_spacing()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal-spacing.qml");

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 60.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 90.0);
    QCOMPARE(three->y(), 0.0);

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QCOMPARE(row->width(), 130.0);
    QCOMPARE(row->height(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_horizontal_spacing_rightToLeft()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal-spacing.qml");

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 80.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 00.0);
    QCOMPARE(three->y(), 0.0);

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QCOMPARE(row->width(), 130.0);
    QCOMPARE(row->height(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_horizontal_animated()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal-animated.qml", false);

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    //Note that they animate in
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(three->x(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QVERIFY(row);
    QCOMPARE(row->width(), 100.0);
    QCOMPARE(row->height(), 50.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->x(), -100.0);//Not 'in' yet
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(three->x(), 50.0);
    QTRY_COMPARE(three->y(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QTRY_COMPARE(two->isVisible(), true);
    QTRY_COMPARE(row->width(), 150.0);
    QTRY_COMPARE(row->height(), 50.0);

    QTest::qWait(0);//Let the animation start
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(three->x(), 50.0);

    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(three->x(), 100.0);

    delete canvas;
}

void tst_qsgpositioners::test_horizontal_animated_rightToLeft()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal-animated.qml", false);

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    //Note that they animate in
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(three->x(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QVERIFY(row);
    QCOMPARE(row->width(), 100.0);
    QCOMPARE(row->height(), 50.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->x(), 50.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->x(), -100.0);//Not 'in' yet
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(three->x(), 0.0);
    QTRY_COMPARE(three->y(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QTRY_COMPARE(two->isVisible(), true);

    // New size should propagate after visible change
    QTRY_COMPARE(row->width(), 150.0);
    QTRY_COMPARE(row->height(), 50.0);

    QTest::qWait(0);//Let the animation start
    QCOMPARE(one->x(), 50.0);
    QCOMPARE(two->x(), -100.0);

    QTRY_COMPARE(one->x(), 100.0);
    QTRY_COMPARE(two->x(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_horizontal_animated_disabled()
{
    QSGView *canvas = createView(SRCDIR "/data/horizontal-animated-disabled.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QSGItem *row = canvas->rootObject()->findChild<QSGItem*>("row");
    QVERIFY(row);

    qApp->processEvents();

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->isVisible(), false);
    QCOMPARE(two->x(), -100.0);//Not 'in' yet
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QCOMPARE(two->isVisible(), true);
    qApp->processEvents();
    QCOMPARE(row->width(), 150.0);
    QCOMPARE(row->height(), 50.0);

    qApp->processEvents();
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(three->x(), 100.0);

    delete canvas;
}

void tst_qsgpositioners::test_vertical()
{
    QSGView *canvas = createView(SRCDIR "/data/vertical.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 0.0);
    QCOMPARE(two->y(), 50.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 60.0);

    QSGItem *column = canvas->rootObject()->findChild<QSGItem*>("column");
    QVERIFY(column);
    QCOMPARE(column->height(), 80.0);
    QCOMPARE(column->width(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_vertical_spacing()
{
    QSGView *canvas = createView(SRCDIR "/data/vertical-spacing.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 0.0);
    QCOMPARE(two->y(), 60.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 80.0);

    QSGItem *column = canvas->rootObject()->findChild<QSGItem*>("column");
    QCOMPARE(column->height(), 100.0);
    QCOMPARE(column->width(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_vertical_animated()
{
    QSGView *canvas = createView(SRCDIR "/data/vertical-animated.qml", false);

    //Note that they animate in
    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QCOMPARE(one->y(), -100.0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QCOMPARE(two->y(), -100.0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QCOMPARE(three->y(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QSGItem *column = canvas->rootObject()->findChild<QSGItem*>("column");
    QVERIFY(column);
    QCOMPARE(column->height(), 100.0);
    QCOMPARE(column->width(), 50.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->y(), -100.0);//Not 'in' yet
    QTRY_COMPARE(two->x(), 0.0);
    QTRY_COMPARE(three->y(), 50.0);
    QTRY_COMPARE(three->x(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QTRY_COMPARE(two->isVisible(), true);
    QTRY_COMPARE(column->height(), 150.0);
    QTRY_COMPARE(column->width(), 50.0);
    QTest::qWait(0);//Let the animation start
    QCOMPARE(two->y(), -100.0);
    QCOMPARE(three->y(), 50.0);

    QTRY_COMPARE(two->y(), 50.0);
    QTRY_COMPARE(three->y(), 100.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid()
{
    QSGView *canvas = createView(SRCDIR "/data/gridtest.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 70.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 50.0);
    QCOMPARE(five->y(), 50.0);

    QSGGrid *grid = canvas->rootObject()->findChild<QSGGrid*>("grid");
    QCOMPARE(grid->flow(), QSGGrid::LeftToRight);
    QCOMPARE(grid->width(), 100.0);
    QCOMPARE(grid->height(), 100.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_topToBottom()
{
    QSGView *canvas = createView(SRCDIR "/data/grid-toptobottom.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 0.0);
    QCOMPARE(two->y(), 50.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 100.0);
    QCOMPARE(four->x(), 50.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 50.0);
    QCOMPARE(five->y(), 50.0);

    QSGGrid *grid = canvas->rootObject()->findChild<QSGGrid*>("grid");
    QCOMPARE(grid->flow(), QSGGrid::TopToBottom);
    QCOMPARE(grid->width(), 100.0);
    QCOMPARE(grid->height(), 120.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_rightToLeft()
{
    QSGView *canvas = createView(SRCDIR "/data/gridtest.qml");

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 50.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 30.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 50.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 40.0);
    QCOMPARE(five->y(), 50.0);

    QSGGrid *grid = canvas->rootObject()->findChild<QSGGrid*>("grid");
    QCOMPARE(grid->layoutDirection(), Qt::RightToLeft);
    QCOMPARE(grid->width(), 100.0);
    QCOMPARE(grid->height(), 100.0);

    // Change the width of the grid and check that items stay to the right
    grid->setWidth(200);
    QTRY_COMPARE(one->x(), 150.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 130.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 100.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 150.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 140.0);
    QCOMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_spacing()
{
    QSGView *canvas = createView(SRCDIR "/data/grid-spacing.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 54.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 78.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 54.0);
    QCOMPARE(five->x(), 54.0);
    QCOMPARE(five->y(), 54.0);

    QSGItem *grid = canvas->rootObject()->findChild<QSGItem*>("grid");
    QCOMPARE(grid->width(), 128.0);
    QCOMPARE(grid->height(), 104.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_row_column_spacing()
{
    QSGView *canvas = createView(SRCDIR "/data/grid-row-column-spacing.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 61.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 92.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 57.0);
    QCOMPARE(five->x(), 61.0);
    QCOMPARE(five->y(), 57.0);

    QSGItem *grid = canvas->rootObject()->findChild<QSGItem*>("grid");
    QCOMPARE(grid->width(), 142.0);
    QCOMPARE(grid->height(), 107.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_animated()
{
    QSGView *canvas = createView(SRCDIR "/data/grid-animated.qml", false);

    canvas->rootObject()->setProperty("testRightToLeft", false);

    //Note that all animate in
    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(one->y(), -100.0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QCOMPARE(three->x(), -100.0);
    QCOMPARE(three->y(), -100.0);

    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QCOMPARE(four->x(), -100.0);
    QCOMPARE(four->y(), -100.0);

    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);
    QCOMPARE(five->x(), -100.0);
    QCOMPARE(five->y(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QSGItem *grid = canvas->rootObject()->findChild<QSGItem*>("grid");
    QVERIFY(grid);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->y(), -100.0);
    QTRY_COMPARE(two->x(), -100.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(three->x(), 50.0);
    QTRY_COMPARE(four->y(), 0.0);
    QTRY_COMPARE(four->x(), 100.0);
    QTRY_COMPARE(five->y(), 50.0);
    QTRY_COMPARE(five->x(), 0.0);

    //Add 'two'
    two->setVisible(true);
    QCOMPARE(two->isVisible(), true);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);
    QTest::qWait(0);//Let the animation start
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);
    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 100.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 0.0);
    QCOMPARE(five->y(), 50.0);
    //Let the animation complete
    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(three->x(), 100.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(four->x(), 0.0);
    QTRY_COMPARE(four->y(), 50.0);
    QTRY_COMPARE(five->x(), 50.0);
    QTRY_COMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_animated_rightToLeft()
{
    QSGView *canvas = createView(SRCDIR "/data/grid-animated.qml", false);

    canvas->rootObject()->setProperty("testRightToLeft", true);

    //Note that all animate in
    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QCOMPARE(one->x(), -100.0);
    QCOMPARE(one->y(), -100.0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QCOMPARE(three->x(), -100.0);
    QCOMPARE(three->y(), -100.0);

    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QCOMPARE(four->x(), -100.0);
    QCOMPARE(four->y(), -100.0);

    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);
    QCOMPARE(five->x(), -100.0);
    QCOMPARE(five->y(), -100.0);

    QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    QSGItem *grid = canvas->rootObject()->findChild<QSGItem*>("grid");
    QVERIFY(grid);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);

    //QTRY_COMPARE used instead of waiting for the expected time of animation completion
    //Note that this means the duration of the animation is NOT tested

    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(one->x(), 100.0);
    QTRY_COMPARE(two->isVisible(), false);
    QTRY_COMPARE(two->y(), -100.0);
    QTRY_COMPARE(two->x(), -100.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(three->x(), 50.0);
    QTRY_COMPARE(four->y(), 0.0);
    QTRY_COMPARE(four->x(), 0.0);
    QTRY_COMPARE(five->y(), 50.0);
    QTRY_COMPARE(five->x(), 100.0);

    //Add 'two'
    two->setVisible(true);
    QCOMPARE(two->isVisible(), true);
    QCOMPARE(grid->width(), 150.0);
    QCOMPARE(grid->height(), 100.0);
    QTest::qWait(0);//Let the animation start
    QCOMPARE(two->x(), -100.0);
    QCOMPARE(two->y(), -100.0);
    QCOMPARE(one->x(), 100.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 100.0);
    QCOMPARE(five->y(), 50.0);
    //Let the animation complete
    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(one->x(), 100.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(three->x(), 0.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(four->x(), 100.0);
    QTRY_COMPARE(four->y(), 50.0);
    QTRY_COMPARE(five->x(), 50.0);
    QTRY_COMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_grid_zero_columns()
{
    QSGView *canvas = createView(SRCDIR "/data/gridzerocolumns.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 70.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 120.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 0.0);
    QCOMPARE(five->y(), 50.0);

    QSGItem *grid = canvas->rootObject()->findChild<QSGItem*>("grid");
    QCOMPARE(grid->width(), 170.0);
    QCOMPARE(grid->height(), 60.0);

    delete canvas;
}

void tst_qsgpositioners::test_propertychanges()
{
    QSGView *canvas = createView(SRCDIR "/data/propertychangestest.qml");

    QSGGrid *grid = qobject_cast<QSGGrid*>(canvas->rootObject());
    QVERIFY(grid != 0);
    QDeclarativeTransition *rowTransition = canvas->rootObject()->findChild<QDeclarativeTransition*>("rowTransition");
    QDeclarativeTransition *columnTransition = canvas->rootObject()->findChild<QDeclarativeTransition*>("columnTransition");

    QSignalSpy addSpy(grid, SIGNAL(addChanged()));
    QSignalSpy moveSpy(grid, SIGNAL(moveChanged()));
    QSignalSpy columnsSpy(grid, SIGNAL(columnsChanged()));
    QSignalSpy rowsSpy(grid, SIGNAL(rowsChanged()));

    QVERIFY(grid);
    QVERIFY(rowTransition);
    QVERIFY(columnTransition);
    QCOMPARE(grid->add(), columnTransition);
    QCOMPARE(grid->move(), columnTransition);
    QCOMPARE(grid->columns(), 4);
    QCOMPARE(grid->rows(), -1);

    grid->setAdd(rowTransition);
    grid->setMove(rowTransition);
    QCOMPARE(grid->add(), rowTransition);
    QCOMPARE(grid->move(), rowTransition);
    QCOMPARE(addSpy.count(),1);
    QCOMPARE(moveSpy.count(),1);

    grid->setAdd(rowTransition);
    grid->setMove(rowTransition);
    QCOMPARE(addSpy.count(),1);
    QCOMPARE(moveSpy.count(),1);

    grid->setAdd(0);
    grid->setMove(0);
    QCOMPARE(addSpy.count(),2);
    QCOMPARE(moveSpy.count(),2);

    grid->setColumns(-1);
    grid->setRows(3);
    QCOMPARE(grid->columns(), -1);
    QCOMPARE(grid->rows(), 3);
    QCOMPARE(columnsSpy.count(),1);
    QCOMPARE(rowsSpy.count(),1);

    grid->setColumns(-1);
    grid->setRows(3);
    QCOMPARE(columnsSpy.count(),1);
    QCOMPARE(rowsSpy.count(),1);

    grid->setColumns(2);
    grid->setRows(2);
    QCOMPARE(columnsSpy.count(),2);
    QCOMPARE(rowsSpy.count(),2);

    delete canvas;
}

void tst_qsgpositioners::test_repeater()
{
    QSGView *canvas = createView(SRCDIR "/data/repeatertest.qml");

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);

    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);

    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 100.0);
    QCOMPARE(three->y(), 0.0);

    delete canvas;
}

void tst_qsgpositioners::test_flow()
{
    QSGView *canvas = createView(SRCDIR "/data/flowtest.qml");

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 0.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 70.0);
    QCOMPARE(five->x(), 50.0);
    QCOMPARE(five->y(), 70.0);

    QSGItem *flow = canvas->rootObject()->findChild<QSGItem*>("flow");
    QVERIFY(flow);
    QCOMPARE(flow->width(), 90.0);
    QCOMPARE(flow->height(), 120.0);

    delete canvas;
}

void tst_qsgpositioners::test_flow_rightToLeft()
{
    QSGView *canvas = createView(SRCDIR "/data/flowtest.qml");

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 40.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 20.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 40.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 40.0);
    QCOMPARE(four->y(), 70.0);
    QCOMPARE(five->x(), 30.0);
    QCOMPARE(five->y(), 70.0);

    QSGItem *flow = canvas->rootObject()->findChild<QSGItem*>("flow");
    QVERIFY(flow);
    QCOMPARE(flow->width(), 90.0);
    QCOMPARE(flow->height(), 120.0);

    delete canvas;
}

void tst_qsgpositioners::test_flow_topToBottom()
{
    QSGView *canvas = createView(SRCDIR "/data/flowtest-toptobottom.qml");

    canvas->rootObject()->setProperty("testRightToLeft", false);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 0.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 50.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 100.0);
    QCOMPARE(four->y(), 00.0);
    QCOMPARE(five->x(), 100.0);
    QCOMPARE(five->y(), 50.0);

    QSGItem *flow = canvas->rootObject()->findChild<QSGItem*>("flow");
    QVERIFY(flow);
    QCOMPARE(flow->height(), 90.0);
    QCOMPARE(flow->width(), 150.0);

    canvas->rootObject()->setProperty("testRightToLeft", true);

    QVERIFY(flow);
    QCOMPARE(flow->height(), 90.0);
    QCOMPARE(flow->width(), 150.0);

    QCOMPARE(one->x(), 100.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 80.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 50.0);
    QCOMPARE(three->y(), 50.0);
    QCOMPARE(four->x(), 0.0);
    QCOMPARE(four->y(), 0.0);
    QCOMPARE(five->x(), 40.0);
    QCOMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_flow_resize()
{
    QSGView *canvas = createView(SRCDIR "/data/flowtest.qml");

    QSGItem *root = qobject_cast<QSGItem*>(canvas->rootObject());
    QVERIFY(root);
    root->setWidth(125);
    root->setProperty("testRightToLeft", false);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QVERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QTRY_COMPARE(one->x(), 0.0);
    QTRY_COMPARE(one->y(), 0.0);
    QTRY_COMPARE(two->x(), 50.0);
    QTRY_COMPARE(two->y(), 0.0);
    QTRY_COMPARE(three->x(), 70.0);
    QTRY_COMPARE(three->y(), 0.0);
    QTRY_COMPARE(four->x(), 0.0);
    QTRY_COMPARE(four->y(), 50.0);
    QTRY_COMPARE(five->x(), 50.0);
    QTRY_COMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_flow_resize_rightToLeft()
{
    QSGView *canvas = createView(SRCDIR "/data/flowtest.qml");

    QSGItem *root = qobject_cast<QSGItem*>(canvas->rootObject());
    QVERIFY(root);
    root->setWidth(125);
    root->setProperty("testRightToLeft", true);

    QSGRectangle *one = canvas->rootObject()->findChild<QSGRectangle*>("one");
    QTRY_VERIFY(one != 0);
    QSGRectangle *two = canvas->rootObject()->findChild<QSGRectangle*>("two");
    QVERIFY(two != 0);
    QSGRectangle *three = canvas->rootObject()->findChild<QSGRectangle*>("three");
    QVERIFY(three != 0);
    QSGRectangle *four = canvas->rootObject()->findChild<QSGRectangle*>("four");
    QVERIFY(four != 0);
    QSGRectangle *five = canvas->rootObject()->findChild<QSGRectangle*>("five");
    QVERIFY(five != 0);

    QCOMPARE(one->x(), 75.0);
    QCOMPARE(one->y(), 0.0);
    QCOMPARE(two->x(), 55.0);
    QCOMPARE(two->y(), 0.0);
    QCOMPARE(three->x(), 5.0);
    QCOMPARE(three->y(), 0.0);
    QCOMPARE(four->x(), 75.0);
    QCOMPARE(four->y(), 50.0);
    QCOMPARE(five->x(), 65.0);
    QCOMPARE(five->y(), 50.0);

    delete canvas;
}

void tst_qsgpositioners::test_flow_implicit_resize()
{
    QSGView *canvas = createView(SRCDIR "/data/flow-testimplicitsize.qml");
    QVERIFY(canvas->rootObject() != 0);

    QSGFlow *flow = canvas->rootObject()->findChild<QSGFlow*>("flow");
    QVERIFY(flow != 0);

    QCOMPARE(flow->width(), 100.0);
    QCOMPARE(flow->height(), 120.0);

    canvas->rootObject()->setProperty("flowLayout", 0);
    QCOMPARE(flow->flow(), QSGFlow::LeftToRight);
    QCOMPARE(flow->width(), 220.0);
    QCOMPARE(flow->height(), 50.0);

    canvas->rootObject()->setProperty("flowLayout", 1);
    QCOMPARE(flow->flow(), QSGFlow::TopToBottom);
    QCOMPARE(flow->width(), 100.0);
    QCOMPARE(flow->height(), 120.0);

    canvas->rootObject()->setProperty("flowLayout", 2);
    QCOMPARE(flow->layoutDirection(), Qt::RightToLeft);
    QCOMPARE(flow->width(), 220.0);
    QCOMPARE(flow->height(), 50.0);

    delete canvas;
}

QString warningMessage;

void interceptWarnings(QtMsgType type, const char *msg)
{
    Q_UNUSED( type );
    warningMessage = msg;
}

void tst_qsgpositioners::test_conflictinganchors()
{
    QtMsgHandler oldMsgHandler = qInstallMsgHandler(interceptWarnings);
    QDeclarativeEngine engine;
    QDeclarativeComponent component(&engine);

    component.setData("import QtQuick 2.0\nColumn { Item {} }", QUrl::fromLocalFile(""));
    QSGItem *item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item {} }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nGrid { Item {} }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nFlow { Item {} }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    delete item;

    component.setData("import QtQuick 2.0\nColumn { Item { anchors.top: parent.top } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Column: Cannot specify top, bottom, verticalCenter, fill or centerIn anchors for items inside Column"));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nColumn { Item { anchors.centerIn: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Column: Cannot specify top, bottom, verticalCenter, fill or centerIn anchors for items inside Column"));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nColumn { Item { anchors.left: parent.left } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item { anchors.left: parent.left } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Row: Cannot specify left, right, horizontalCenter, fill or centerIn anchors for items inside Row"));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item { anchors.fill: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Row: Cannot specify left, right, horizontalCenter, fill or centerIn anchors for items inside Row"));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nRow { Item { anchors.top: parent.top } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QVERIFY(warningMessage.isEmpty());
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nGrid { Item { anchors.horizontalCenter: parent.horizontalCenter } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Grid: Cannot specify anchors for items inside Grid"));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nGrid { Item { anchors.centerIn: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Grid: Cannot specify anchors for items inside Grid"));
    warningMessage.clear();
    delete item;

    component.setData("import QtQuick 2.0\nFlow { Item { anchors.verticalCenter: parent.verticalCenter } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Flow: Cannot specify anchors for items inside Flow"));
    delete item;

    component.setData("import QtQuick 2.0\nFlow { Item { anchors.fill: parent } }", QUrl::fromLocalFile(""));
    item = qobject_cast<QSGItem*>(component.create());
    QVERIFY(item);
    QCOMPARE(warningMessage, QString("file::2:1: QML Flow: Cannot specify anchors for items inside Flow"));
    qInstallMsgHandler(oldMsgHandler);
    delete item;
}

void tst_qsgpositioners::test_mirroring()
{
    QList<QString> qmlFiles;
    qmlFiles << "horizontal.qml" << "gridtest.qml" << "flowtest.qml";
    QList<QString> objectNames;
    objectNames << "one" << "two" << "three" << "four" << "five";

    foreach(const QString qmlFile, qmlFiles) {
        QSGView *canvasA = createView(QString(SRCDIR) + "/data/" + qmlFile);
        QSGItem *rootA = qobject_cast<QSGItem*>(canvasA->rootObject());

        QSGView *canvasB = createView(QString(SRCDIR) + "/data/" + qmlFile);
        QSGItem *rootB = qobject_cast<QSGItem*>(canvasB->rootObject());

        rootA->setProperty("testRightToLeft", true); // layoutDirection: Qt.RightToLeft

        // LTR != RTL
        foreach(const QString objectName, objectNames) {
            // horizontal.qml only has three items
            if (qmlFile == QString("horizontal.qml") && objectName == QString("four"))
                break;
            QSGItem *itemA = rootA->findChild<QSGItem*>(objectName);
            QSGItem *itemB = rootB->findChild<QSGItem*>(objectName);
            QTRY_VERIFY(itemA->x() != itemB->x());
        }

        QSGItemPrivate* rootPrivateB = QSGItemPrivate::get(rootB);

        rootPrivateB->effectiveLayoutMirror = true; // LayoutMirroring.enabled: true
        rootPrivateB->isMirrorImplicit = false;
        rootPrivateB->inheritMirrorFromItem = true; // LayoutMirroring.childrenInherit: true
        rootPrivateB->resolveLayoutMirror();

        // RTL == mirror
        foreach(const QString objectName, objectNames) {
            // horizontal.qml only has three items
            if (qmlFile == QString("horizontal.qml") && objectName == QString("four"))
                break;
            QSGItem *itemA = rootA->findChild<QSGItem*>(objectName);
            QSGItem *itemB = rootB->findChild<QSGItem*>(objectName);
            QTRY_COMPARE(itemA->x(), itemB->x());
        }

        rootA->setProperty("testRightToLeft", false); // layoutDirection: Qt.LeftToRight
        rootB->setProperty("testRightToLeft", true); // layoutDirection: Qt.RightToLeft

        // LTR == RTL + mirror
        foreach(const QString objectName, objectNames) {
            // horizontal.qml only has three items
            if (qmlFile == QString("horizontal.qml") && objectName == QString("four"))
                break;
            QSGItem *itemA = rootA->findChild<QSGItem*>(objectName);
            QSGItem *itemB = rootB->findChild<QSGItem*>(objectName);
            QTRY_COMPARE(itemA->x(), itemB->x());
        }
        delete canvasA;
        delete canvasB;
    }
}

void tst_qsgpositioners::test_allInvisible()
{
    //QTBUG-19361
    QSGView *canvas = createView(SRCDIR "/data/allInvisible.qml");

    QSGItem *root = qobject_cast<QSGItem*>(canvas->rootObject());
    QVERIFY(root);

    QSGRow *row = canvas->rootObject()->findChild<QSGRow*>("row");
    QVERIFY(row != 0);
    QVERIFY(row->width() == 0);
    QVERIFY(row->height() == 0);
    QSGColumn *column = canvas->rootObject()->findChild<QSGColumn*>("column");
    QVERIFY(column != 0);
    QVERIFY(column->width() == 0);
    QVERIFY(column->height() == 0);
}

void tst_qsgpositioners::test_attachedproperties()
{
    QFETCH(QString, filename);

    QSGView *canvas = createView(filename);
    QVERIFY(canvas->rootObject() != 0);

    QSGRectangle *greenRect = canvas->rootObject()->findChild<QSGRectangle *>("greenRect");
    QVERIFY(greenRect != 0);

    int posIndex = greenRect->property("posIndex").toInt();
    QVERIFY(posIndex == 0);
    bool isFirst = greenRect->property("isFirstItem").toBool();
    QVERIFY(isFirst == true);
    bool isLast = greenRect->property("isLastItem").toBool();
    QVERIFY(isLast == false);

    QSGRectangle *yellowRect = canvas->rootObject()->findChild<QSGRectangle *>("yellowRect");
    QVERIFY(yellowRect != 0);

    posIndex = yellowRect->property("posIndex").toInt();
    QVERIFY(posIndex == -1);
    isFirst = yellowRect->property("isFirstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = yellowRect->property("isLastItem").toBool();
    QVERIFY(isLast == false);

    yellowRect->metaObject()->invokeMethod(yellowRect, "onDemandPositioner");

    posIndex = yellowRect->property("posIndex").toInt();
    QVERIFY(posIndex == 1);
    isFirst = yellowRect->property("isFirstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = yellowRect->property("isLastItem").toBool();
    QVERIFY(isLast == true);

    delete canvas;
}

void tst_qsgpositioners::test_attachedproperties_data()
{
    QTest::addColumn<QString>("filename");

    QTest::newRow("column") << SRCDIR "/data/attachedproperties-column.qml";
    QTest::newRow("row") << SRCDIR "/data/attachedproperties-row.qml";
    QTest::newRow("grid") << SRCDIR "/data/attachedproperties-grid.qml";
    QTest::newRow("flow") << SRCDIR "/data/attachedproperties-flow.qml";
}

void tst_qsgpositioners::test_attachedproperties_dynamic()
{
    QSGView *canvas = createView(SRCDIR "/data/attachedproperties-dynamic.qml");
    QVERIFY(canvas->rootObject() != 0);

    QSGRow *row = canvas->rootObject()->findChild<QSGRow *>("pos");
    QVERIFY(row != 0);

    QSGRectangle *rect0 = canvas->rootObject()->findChild<QSGRectangle *>("rect0");
    QVERIFY(rect0 != 0);

    int posIndex = rect0->property("index").toInt();
    QVERIFY(posIndex == 0);
    bool isFirst = rect0->property("firstItem").toBool();
    QVERIFY(isFirst == true);
    bool isLast = rect0->property("lastItem").toBool();
    QVERIFY(isLast == false);

    QSGRectangle *rect1 = canvas->rootObject()->findChild<QSGRectangle *>("rect1");
    QVERIFY(rect1 != 0);

    posIndex = rect1->property("index").toInt();
    QVERIFY(posIndex == 1);
    isFirst = rect1->property("firstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = rect1->property("lastItem").toBool();
    QVERIFY(isLast == true);

    row->metaObject()->invokeMethod(row, "createSubRect");

    QTRY_VERIFY(rect1->property("index").toInt() == 1);
    QTRY_VERIFY(rect1->property("firstItem").toBool() == false);
    QTRY_VERIFY(rect1->property("lastItem").toBool() == false);

    QSGRectangle *rect2 = canvas->rootObject()->findChild<QSGRectangle *>("rect2");
    QVERIFY(rect2 != 0);

    posIndex = rect2->property("index").toInt();
    QVERIFY(posIndex == 2);
    isFirst = rect2->property("firstItem").toBool();
    QVERIFY(isFirst == false);
    isLast = rect2->property("lastItem").toBool();
    QVERIFY(isLast == true);

    row->metaObject()->invokeMethod(row, "destroySubRect");

    qApp->processEvents(QEventLoop::DeferredDeletion);

    QTRY_VERIFY(rect1->property("index").toInt() == 1);
    QTRY_VERIFY(rect1->property("firstItem").toBool() == false);
    QTRY_VERIFY(rect1->property("lastItem").toBool() == true);

    delete canvas;
}

QSGView *tst_qsgpositioners::createView(const QString &filename, bool wait)
{
    QSGView *canvas = new QSGView(0);

    canvas->setSource(QUrl::fromLocalFile(filename));
    canvas->show();
    if (wait)
        QTest::qWaitForWindowShown(canvas); //It may not relayout until the next frame, so it needs to be drawn

    return canvas;
}


QTEST_MAIN(tst_qsgpositioners)

#include "tst_qsgpositioners.moc"
