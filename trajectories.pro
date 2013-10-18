QT += widgets webkitwidgets xml json

# Add more folders to ship with the application, here
folder_01.source = html
folder_01.target = .
DEPLOYMENTFOLDERS = folder_01

QMAKE_CXXFLAGS += -std=c++11

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    trajectories/trajectories.cpp \
    trajectories/serializer.cpp

include(libs.pri)
include(html5bridgeviewer/html5bridgeviewer.pri)
include(simulator/simulator.pri)

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    trajectories/trajectories.h \
    trajectories/serializer.h
