#include <QGraphicsWebView>
#include <QApplication>
#include <QWebInspector>

#include "html5applicationviewer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.webView()->setAcceptHoverEvents(true);

    viewer.webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    QWebInspector inspector;
    inspector.setPage(viewer.webView()->page());
    inspector.setVisible(true);

    viewer.showExpanded();
    viewer.loadFile(QLatin1String("html/index.html"));

    return app.exec();
}
