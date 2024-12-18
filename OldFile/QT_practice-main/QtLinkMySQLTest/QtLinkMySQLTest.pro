QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    characterreference.cpp \
    initbydatabase.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    character.h \
    characterreference.h \
    initbydatabase.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QT += core
QT       += core gui
QT +=core gui sql
QT+=sql

CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
 QMAKE_CXXFLAGS += -std:c++17 /Zc:__cplusplus
 win32: {
     QMAKE_CXXFLAGS += /permissive-
 }

 MSVC: {
     QMAKE_CXXFLAGS += /permissive-
 }
 QMAKE_CXXFLAGS += -std=c++17
