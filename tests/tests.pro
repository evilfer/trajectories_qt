TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    dummyworldloader_tests.cpp \
    helpers/dummyworldloader.cpp \
    emptyworld_tests.cpp \
    helpers/missioncreator.cpp \
    trivialworldmissions_tests.cpp

HEADERS += \
    helpers/dummyworldloader.h \
    helpers/missioncreator.h


include(testlibs.pri)

OTHER_FILES += \
    testlibs.pri

LIBS += -L$$OUT_PWD/../simulator/ -lsimulator

INCLUDEPATH += $$PWD/../simulator
DEPENDPATH += $$PWD/../simulator

PRE_TARGETDEPS += $$OUT_PWD/../simulator/libsimulator.a

