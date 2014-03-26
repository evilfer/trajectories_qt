QT += widgets webkitwidgets

LIBS += -lsqlite3 -lqjson


# Add more folders to ship with the application, here
folder_html.source = html
folder_html.target = .
folder_cfg.source = cfg
folder_cfg.target = .

DEPLOYMENTFOLDERS = folder_html folder_cfg

QMAKE_CXXFLAGS += -std=c++11

# Define TOUCH_OPTIMIZED_NAVIGATION for touch optimization and flicking
#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

include(html5bridgeviewer/html5bridgeviewer.pri)
include(trajectories/trajectories.pri)
include(libs.pri)

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)

qtcAddDeployment()


unix:!macx: LIBS += -L$$OUT_PWD/../simulator/ -lsimulator

INCLUDEPATH += $$PWD/../simulator
DEPENDPATH += $$PWD/../simulator

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../simulator/libsimulator.a


