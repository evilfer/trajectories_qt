/*

Copyright (C) 2010-2013 Eloy David Villasclaras Fernandez.
evilfer@gmail.com

This file is part of Trajectories.

Trajectories is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Trajectories is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Trajectories.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "html5trajectoriesviewer.h"

#include <QGraphicsWebView>
#include <QWebFrame>

#include "cppjavascriptbridge.h"

namespace bridge {

    Html5TrajectoriesViewer::Html5TrajectoriesViewer(CppJavascriptBridgeListener * listener) : Html5ApplicationViewer(), listener_(listener) {
        QObject::connect(this->webView()->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),this, SLOT(addJavascriptObject()));


        this->setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
        this->webView()->setAcceptHoverEvents(true);
        this->webView()->setAcceptDrops(true);

        this->webView()->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    }

    void Html5TrajectoriesViewer::addJavascriptObject() {
        this->webView()->page()->mainFrame()->addToJavaScriptWindowObject(QString("QtCppJsBridge"), new CppJavascriptBridge(this->listener_));
    }

}
