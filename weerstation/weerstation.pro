QT       += core gui widgets charts sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbase.cpp \
    main.cpp \
    mainwindow.cpp \
    wchart.cpp

HEADERS += \
    dbase.h \
    mainwindow.h \
    wchart.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += "C:/Program Files (x86)/Visual Leak Detector/include/"
LIBS      += -L"C:/Program Files (x86)/Visual Leak Detector/lib/Win64"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_FILE = weatherstation.rc
