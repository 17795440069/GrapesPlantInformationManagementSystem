QT       += core gui serialport network sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configwight.cpp \
    grapesalesinsert.cpp \
    growthrecordsinsert.cpp \
    harvestrecordsinsert.cpp \
    informationwight.cpp \
    ini_file.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    meteorologicalinformationinsert.cpp \
    monitoringinformationwight.cpp \
    pesticidesfertilizersinsert.cpp \
    plantinformationwight.cpp \
    plantingbaseinsert.cpp \
    plantingcropsinsert.cpp \
    sharevar.cpp

HEADERS += \
    configwight.h \
    connection.h \
    grapesalesinsert.h \
    growthrecordsinsert.h \
    harvestrecordsinsert.h \
    informationwight.h \
    ini_file.h \
    login.h \
    mainwindow.h \
    meteorologicalinformationinsert.h \
    monitoringinformationwight.h \
    pesticidesfertilizersinsert.h \
    plantinformationwight.h \
    plantingbaseinsert.h \
    plantingcropsinsert.h \
    sharevar.h

FORMS += \
    configwight.ui \
    grapesalesinsert.ui \
    growthrecordsinsert.ui \
    harvestrecordsinsert.ui \
    informationwight.ui \
    login.ui \
    mainwindow.ui \
    meteorologicalinformationinsert.ui \
    monitoringinformationwight.ui \
    pesticidesfertilizersinsert.ui \
    plantinformationwight.ui \
    plantingbaseinsert.ui \
    plantingcropsinsert.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
