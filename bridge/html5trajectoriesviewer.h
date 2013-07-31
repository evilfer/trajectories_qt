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
