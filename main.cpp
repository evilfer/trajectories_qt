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
