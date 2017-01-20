TEMPLATE = app

QT += qml quick widgets xmlpatterns
INCLUDEPATH += /home/hekra01/qtwebdriver/out/dist/desktop/release/Test
INCLUDEPATH += /home/hekra01/qtwebdriver/out/dist/desktop/release/h
LIBS += -L/home/hekra01/qtwebdriver/out/dist/desktop/release/libs
LIBS += -lchromium_base -lWebDriver_core -lWebDriver_extension_qt_base -lWebDriver_extension_qt_quick -lWebDriver_extension_qt_quick_web -lWebDriver_extension_qt_web
DEFINES += QT_NO_SAMPLES="1"

SOURCES += main.cpp

lupdate_only{
SOURCES = *.qml \
          PhotoViewerCore/*.qml \
          PhotoViewerCore/script/*.js
}

TRANSLATIONS += i18n/qml_fr.ts \
                i18n/qml_de.ts

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
