CONFIG += testcase
TARGET = tst_qquickstates
macx:CONFIG -= app_bundle

SOURCES += tst_qquickstates.cpp

include (../../shared/util.pri)

TESTDATA = data/*

CONFIG += parallel_test
QT += core-private gui-private v8-private qml-private quick-private opengl-private testlib
