#-------------------------------------------------
#
# Project created by QtCreator 2013-12-11T21:55:16
#
#-------------------------------------------------

QT       += core widgets webkitwidgets

TARGET = ui
TEMPLATE = lib

DEFINES += UI_LIBRARY

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

HEADERS += \
    ui_global.h \
    app/appdockbar.h \
    app/appsetupmenu.h \
    app/appsplitter.h \
    app/appstatusbar.h \
    app/appui.h \
    app/bppmarkdown.h \
    base/basestatusbar.h \
    base/basetoolbar.h \
    model/fileinfo.h \
    util/apputil.h \
    include/appparam.h \
    include/buildnames.h \
    include/transnames.h

SOURCES += \
    app/appdockbar.cpp \
    app/appsetupmenu.cpp \
    app/appsplitter.cpp \
    app/appstatusbar.cpp \
    app/appui.cpp \
    app/bppmarkdown.cpp \
    base/basestatusbar.cpp \
    base/basetoolbar.cpp \
    model/fileinfo.cpp \
    util/apputil.cpp \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script/release/ -lscript
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script/debug/ -lscript

INCLUDEPATH += $$PWD/../script
DEPENDPATH += $$PWD/../script
