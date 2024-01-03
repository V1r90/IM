<<<<<<< HEAD
QT += gui widgets
QT += sql network
=======
QT -= gui
QT += sql core network
>>>>>>> 41f8a5972cbd57d0b1a15843c04e8327d493d2b0

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Database.cpp \
        MsgHandle.cpp \
<<<<<<< HEAD
        ServerSocket.cpp \
        main.cpp \
        serverwidget.cpp
=======
        MsgPackage.cpp \
        Server.cpp \
        main.cpp
>>>>>>> 41f8a5972cbd57d0b1a15843c04e8327d493d2b0

# chinese
# QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Database.h \
    MsgHandle.h \
    MsgPackage.h \
<<<<<<< HEAD
    ServerSocket.h \
    serverwidget.h

FORMS += \
    serverwidget.ui
=======
    Server.h
>>>>>>> 41f8a5972cbd57d0b1a15843c04e8327d493d2b0
