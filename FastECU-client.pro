QT       += core gui remoteobjects websockets serialport
REPC_SOURCE = \
    serial_port/serial_port_actions.rep \
    remote_utility/remote_utility.rep

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    remote_utility/remote_utility.cpp \
    serial_port/serial_port_actions.cpp \
    serial_port/serial_port_actions_direct.cpp \
    serial_port/websocketiodevice.cpp \
    startup.cpp

HEADERS += \
    mainwindow.h \
    remote_utility/remote_utility.h \
    serial_port/serial_port_actions.h \
    serial_port/serial_port_actions_direct.h \
    serial_port/websocketiodevice.h \
    startup.h

win32 {
    SOURCES += \
    serial_port/J2534_win.cpp
    HEADERS += \
    serial_port/J2534_win.h
    HEADERS += \
    serial_port/J2534_tactrix_win.h
}
linux {
    SOURCES += \
    serial_port/J2534_linux.cpp
    HEADERS += \
    serial_port/J2534_linux.h
    HEADERS += \
    serial_port/J2534_tatrix_linux.h \
}

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
