#-------------------------------------------------
#
# Project created by QtCreator 2014-03-23T17:17:26
#
#-------------------------------------------------

QT       -= gui

TARGET = simulator
TEMPLATE = lib
CONFIG += dll


DEFINES += SIMULATOR_LIBRARY

QMAKE_CXXFLAGS += -std=c++11

include(libs.pri)


HEADERS += \
    simulator.h \
    ephemerides/bodyconstants.h \
    ephemerides/spiceposition.h \
    tmath/consts.h \
    tmath/julianday.h \
    tmath/vectormath.h \
    trajectory/pathpoint.h \
    trajectory/pathsection.h \
    trajectory/trajectory.h \
    world/body.h \
    world/burn.h \
    world/gravityfield.h \
    world/interpolator.h \
    world/irregularorbit.h \
    world/object.h \
    world/orbit.h \
    world/planetsystem.h \
    world/ship.h \
    world/solarsystem.h \
    world/world.h \
    world/worldloader.h \
    structs/missiondata.h \
    trajectory/trajectorydata.h

SOURCES += \
    simulator.cpp \
    ephemerides/bodyconstants.cpp \
    ephemerides/spiceposition.cpp \
    tmath/julianday.cpp \
    tmath/vectormath.cpp \
    trajectory/pathpoint.cpp \
    trajectory/pathsection.cpp \
    trajectory/trajectory.cpp \
    world/body.cpp \
    world/burn.cpp \
    world/gravityfield.cpp \
    world/interpolator.cpp \
    world/irregularorbit.cpp \
    world/object.cpp \
    world/orbit.cpp \
    world/planetsystem.cpp \
    world/ship.cpp \
    world/solarsystem.cpp \
    world/world.cpp \
    world/worldloader.cpp \
    trajectory/trajectorydata.cpp
