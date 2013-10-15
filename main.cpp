#include <QApplication>
#include <QWebInspector>
#include <QGraphicsWebView>

#include "html5bridgeviewer/html5bridgeviewer.h"
#include "html5bridgeviewer/cppjavascriptbridgelistener.h"


class TestBridgeListener : public bridge::CppJavascriptBridgeListener {

    //QVariantMap processCall(int op, int opId, QVariantMap & data);

    QVariantMap processCall(QString &, QVariantMap &) {
        QVariantMap result = QVariantMap();
        result["test"] = "Test!";
        return result;
    }

};


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    bridge::Html5BridgeViewer viewer(new TestBridgeListener());
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);


    QWebInspector inspector;
    inspector.setPage(viewer.webView()->page());
    inspector.setGeometry(20, 500, 600, 400);
    inspector.setVisible(true);

    viewer.setGeometry(20, 30, 600, 400);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("html/index.html"));

    return app.exec();
}
