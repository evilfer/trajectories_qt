greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
folder_01.source = html
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    trajectory/path.cpp \
    trajectory/pathpoint.cpp \
    trajectory/pathsection.cpp \
    tmath/vectormath.cpp \
    tmath/julianday.cpp \
    win/strptime.cpp \
    world/ship.cpp \
    ephemerides/bodyconstants.cpp \
    ephemerides/spiceposition.cpp \
    world/body.cpp \
    world/gravityfield.cpp \
    world/interpolator.cpp \
    world/object.cpp \
    world/orbit.cpp \
    world/planetsystem.cpp \
    world/solarsystem.cpp \
    world/world.cpp \
    world/worldloader.cpp \
    world/burn.cpp \
    trajectory/trajectory.cpp

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

include(cspicelib.pri)

HEADERS += \
    trajectory/path.h \
    trajectory/pathpoint.h \
    trajectory/pathsection.h \
    tmath/vectormath.h \
    tmath/consts.h \
    tmath/julianday.h \
    win/strptime.h \
    world/ship.h \
    world/body.h \
    world/gravityfield.h \
    world/interpolator.h \
    world/object.h \
    world/orbit.h \
    world/planetsystem.h \
    world/solarsystem.h \
    world/world.h \
    world/worldloader.h \
    ephemerides/bodyconstants.h \
    ephemerides/spiceposition.h \
    world/burn.h \
    trajectory/trajectory.h

OTHER_FILES += \
    cfg/kernels.furnsh \
    cfg/default.txt \
    cfg/colors.cfg \
    cspicelib.pri.default


