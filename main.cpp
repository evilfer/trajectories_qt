#include <QGraphicsWebView>
#include <QApplication>
#include <QWebInspector>
#include <QWebFrame>

#include "html5applicationviewer.h"

#include "bridge/cppjavascriptbridge.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.webView()->setAcceptHoverEvents(true);

    viewer.webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    QWebInspector inspector;
    inspector.setPage(viewer.webView()->page());
    inspector.setGeometry(20, 500, 600, 400);
    inspector.setVisible(true);

    viewer.setGeometry(20, 30, 600, 400);
    viewer.showExpanded();
    viewer.loadFile(QString("html/index.html"));
    viewer.webView()->page()->mainFrame()->addToJavaScriptWindowObject(QString("QtCppJsBridge"), new bridge::CppJavascriptBridge());

    return app.exec();
}
