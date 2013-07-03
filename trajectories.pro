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
    ephemerides/SpicePosition.cpp \
    ephemerides/BodyConstants.cpp

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    trajectory/path.h \
    trajectory/pathpoint.h \
    trajectory/pathsection.h \
    tmath/vectormath.h \
    tmath/consts.h \
    tmath/julianday.h \
    win/strptime.h \
    ephemerides/SpicePosition.h \
    ephemerides/BodyConstants.h

OTHER_FILES += \
    cfg/kernels.furnsh \
    cfg/default.txt \
    cfg/colors.cfg
