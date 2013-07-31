#include "html5trajectoriesviewer.h"

#include <QGraphicsWebView>
#include <QWebFrame>

#include "trajectoriesbridge.h"

namespace bridge {

    Html5TrajectoriesViewer::Html5TrajectoriesViewer() : Html5ApplicationViewer() {
        QObject::connect(this->webView()->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJavascriptObject()));


        this->setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
        this->webView()->setAcceptHoverEvents(true);
        this->webView()->setAcceptDrops(true);

        this->webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    }

    void Html5TrajectoriesViewer::addJavascriptObject() {
        this->webView()->page()->mainFrame()->addToJavaScriptWindowObject(QString("QtCppJsBridge"), new TrajectoriesBridge());
    }

}
