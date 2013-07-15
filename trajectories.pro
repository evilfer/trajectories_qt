greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
html_folder.source = html
html_folder.target = .
DEPLOYMENTFOLDERS = html_folder

#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    ephemerides/spiceposition.cpp \
    ephemerides/bodyconstants.cpp \
    tmath/vectormath.cpp \
    tmath/julianday.cpp \
    trajectory/trajectory.cpp \
    trajectory/pathsection.cpp \
    trajectory/pathpoint.cpp \
    trajectory/path.cpp \
    win/strptime.cpp \
    world/worldloader.cpp \
    world/world.cpp \
    world/solarsystem.cpp \
    world/ship.cpp \
    world/planetsystem.cpp \
    world/orbit.cpp \
    world/object.cpp \
    world/interpolator.cpp \
    world/gravityfield.cpp \
    world/burn.cpp \
    world/body.cpp


HEADERS += \
    ephemerides/spiceposition.h \
    ephemerides/bodyconstants.h \
    tmath/vectormath.h \
    tmath/julianday.h \
    tmath/consts.h \
    trajectory/trajectory.h \
    trajectory/pathsection.h \
    trajectory/pathpoint.h \
    trajectory/path.h \
    win/strptime.h \
    world/worldloader.h \
    world/world.h \
    world/solarsystem.h \
    world/ship.h \
    world/planetsystem.h \
    world/orbit.h \
    world/object.h \
    world/interpolator.h \
    world/gravityfield.h \
    world/burn.h \
    world/body.h

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
include(cspicelib.pri)

qtcAddDeployment()

OTHER_FILES += \
    cfg/kernels.furnsh


