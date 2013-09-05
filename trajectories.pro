greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
html_folder.source = html
html_folder.target = .
cfg_folder.source = cfg
cfg_folder.target = .

DEPLOYMENTFOLDERS = html_folder cfg_folder

#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    trajectories.cpp \
    trajectories_init.cpp


include(cspicelib.pri)
include(simulator/simulator.pri)
include(bridge/bridge.pri)
include(model/model.pri)
include(win/win.pri)

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()


LIBS += -lsqlite3

HEADERS += \
    trajectories.h

