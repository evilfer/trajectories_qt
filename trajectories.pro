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

QMAKE_CXXFLAGS += -std=c++0x

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    trajectories_init.cpp \
    trajectories.cpp

include(libs.pri)
include(simulator/simulator.pri)
include(bridge/bridge.pri)
include(model/model.pri)
include(win/win.pri)

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    trajectories.h
