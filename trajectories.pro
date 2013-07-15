greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
html_folder.source = html
html_folder.target = .
cfg_folder.source = cfg
cfg_folder.target = .

DEPLOYMENTFOLDERS = html_folder cfg_folder

#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp


include(cspicelib.pri)
include(backend.pri)
include(bridge.pri)

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    cfg/kernels.furnsh \
    backend.pri \
    bridge.pri


