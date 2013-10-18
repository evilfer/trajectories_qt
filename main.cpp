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

#include <QApplication>
#include <QWebInspector>
#include <QGraphicsWebView>

#include "trajectories/trajectories.h"
#include "html5bridgeviewer/html5bridgeviewer.h"



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    bridge::Html5BridgeViewer viewer(new Trajectories());

    QWebInspector inspector;
    inspector.setPage(viewer.webView()->page());
    inspector.setGeometry(20, 500, 600, 400);
    inspector.setVisible(true);

    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.setGeometry(20, 30, 600, 400);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("../html/index.html"));

    return app.exec();
}
