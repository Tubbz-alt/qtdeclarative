load(qttest_p4)
contains(QT_CONFIG,declarative): QT += declarative widgets
macx:CONFIG -= app_bundle

SOURCES += tst_qdeclarativeproperty.cpp

DEFINES += SRCDIR=\\\"$$PWD\\\"

CONFIG += parallel_test

QT += core-private gui-private v8-private declarative-private
