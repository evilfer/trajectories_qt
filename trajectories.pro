greaterThan(QT_MAJOR_VERSION, 4):QT += widgets webkitwidgets

# Add more folders to ship with the application, here
html_folder.source = html
html_folder.target = .
DEPLOYMENTFOLDERS = html_folder

#DEFINES += TOUCH_OPTIMIZED_NAVIGATION

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    ephemerides/spiceposition.cpp \
    ephemerides/bodyconstants.cpp


HEADERS += \
    ephemerides/spiceposition.h \
    ephemerides/bodyconstants.h

# Please do not modify the following two lines. Required for deployment.
include(html5applicationviewer/html5applicationviewer.pri)
include(cspicelib.pri)

qtcAddDeployment()


