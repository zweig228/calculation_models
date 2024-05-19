QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    geometry_sb.cpp \
    init_kinematic.cpp \
    init_termo.cpp \
    kinematic.cpp \
    main.cpp \
    mainwindow.cpp \
    termo.cpp

HEADERS += \
    constants.h \
    geometry_sb.h \
    init_kinematic.h \
    init_termo.h \
    kinematic.h \
    mainwindow.h \
    ring_object_manager.h \
    termo.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    segments.txt
