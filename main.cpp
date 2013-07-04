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
#include <QWebView>
#include <QtWebKit/QWebView>
#include <QGraphicsWebView>

#include "html5applicationviewer.h"
#include <stdio.h>

#include "world/solarsystem.h"
#include "world/worldloader.h"
#include "ephemerides/spiceposition.h"

int main(int argc, char *argv[]) {

    ephemerides::SpicePosition::init();

    world::SolarSystem * s= world::WorldLoader::loadSolarSystem();
    s->wakeUpAllSystems();

    QApplication app(argc, argv);

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.webView()->setAcceptHoverEvents(true);
    viewer.webView()->setActive(true);

    viewer.loadUrl(QUrl("html/index.html"));

    return app.exec();

}
