#ifndef HTML5TRAJECTORIESVIEWER_H
#define HTML5TRAJECTORIESVIEWER_H

#include "../html5applicationviewer/html5applicationviewer.h"

namespace bridge {

    class Html5TrajectoriesViewer : public Html5ApplicationViewer {
        Q_OBJECT

        bool javascriptAdded_;

    public:
        Html5TrajectoriesViewer();

    public slots:
        void addJavascriptObject();
    };

}

#endif // HTML5TRAJECTORIESVIEWER_H
