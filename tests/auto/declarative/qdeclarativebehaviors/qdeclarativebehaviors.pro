load(qttest_p4)
contains(QT_CONFIG,declarative): QT += declarative opengl
SOURCES += tst_qdeclarativebehaviors.cpp
macx:CONFIG -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD\\\"

CONFIG += parallel_test insignificant_test

QT += core-private gui-private v8-private declarative-private opengl-private
