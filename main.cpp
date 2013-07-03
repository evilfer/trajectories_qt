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
#include "html5applicationviewer.h"

#include "trajectory/path.h"

int main(int argc, char *argv[])
{


  trajectory::PathPoint point;
  trajectory::Path path;

  trajectory::PathPosition p0 = path.startSection(point);
  point.setT(1);
  path.save(point);
  point.setT(2);
  path.save(point);

  trajectory::PathPosition p1 = path.endSection();

  QApplication app(argc, argv);

  Html5ApplicationViewer viewer;
  viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
  viewer.showExpanded();
  viewer.loadFile(QLatin1String("html/index.html"));

  return app.exec();

}
