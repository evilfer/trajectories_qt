#include <QGraphicsWebView>
#include <QApplication>
#include <QWebInspector>
#include <QWebFrame>

#include "bridge/html5trajectoriesviewer.h"

#include "bridge/trajectoriesbridge.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    bridge::Html5TrajectoriesViewer viewer;

    QWebInspector inspector;
    inspector.setPage(viewer.webView()->page());
    inspector.setGeometry(20, 500, 600, 400);
    inspector.setVisible(true);

    viewer.setGeometry(20, 30, 600, 400);
    viewer.showExpanded();
    viewer.loadFile(QString("html/index.html"));


    return app.exec();
}
