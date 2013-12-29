#-------------------------------------------------
#
# Project created by QtCreator 2013-12-12T22:58:53
#
# 该项目使用js来解析markdown文本或者将html转换为markdown
#
#-------------------------------------------------

QT       -= gui

TARGET = script
TEMPLATE = lib

INCLUDEPATH += ../include

DEFINES += SCRIPT_LIBRARY

SOURCES += script.cpp

HEADERS += script.h\
        script_global.h

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/v8/release/ -lv8_base.ia32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/v8/debug/ -lv8_base.ia32

INCLUDEPATH += $$PWD/../lib/v8/debug \
                $$PWD/../lib/v8/release
DEPENDPATH += $$PWD/../lib/v8/debug \
                $$PWD/../lib/v8/release
