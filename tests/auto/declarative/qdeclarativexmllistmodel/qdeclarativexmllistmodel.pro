load(qttest_p4)
contains(QT_CONFIG,declarative): QT += declarative gui network
contains(QT_CONFIG,xmlpatterns) {
    QT += xmlpatterns
    DEFINES += QTEST_XMLPATTERNS
}
macx:CONFIG -= app_bundle

SOURCES += tst_qdeclarativexmllistmodel.cpp

DEFINES += SRCDIR=\\\"$$PWD\\\"

CONFIG += parallel_test

QT += core-private gui-private v8-private declarative-private
