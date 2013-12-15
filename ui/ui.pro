#-------------------------------------------------
#
# Project created by QtCreator 2013-12-11T21:55:16
#
#-------------------------------------------------

QT       += core gui webkitwidgets

TARGET = ui
TEMPLATE = lib

DEFINES += UI_LIBRARY

SOURCES += \
    app/bppmarkdown.cpp \
    app/appstatusbar.cpp \
    app/appsplitter.cpp \
    app/appdockbar.cpp \
    base/basetoolbar.cpp \
    base/basestatusbar.cpp \
    app/appui.cpp \
    app/appsetupmenu.cpp

HEADERS +=\
        ui_global.h \
    app/bppmarkdown.h \
    app/appstatusbar.h \
    app/appsplitter.h \
    app/appdockbar.h \
    base/basetoolbar.h \
    base/basestatusbar.h \
    include/transnames.h \
    include/buildnames.h \
    include/appparam.h \
    app/appui.h \
    app/appsetupmenu.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    skin/default.qss

RESOURCES += \
    res.qrc
