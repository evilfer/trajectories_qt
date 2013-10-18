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

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QString>
#include <QFile>


class Serializer {
public:
    static void save(QFile & file, const QString & rootElementTagName, const QVariantMap &data);
    static QVariantMap load(QFile & file);

    static QDomDocument write(const QString & rootElementTagName, const QVariantMap & map);
    static QVariantMap read(const QDomDocument & doc);

private:
    static void writeValue(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer);

    static void writeMap(const QString & tagName, const QVariantMap & map, QDomDocument & document, QDomNode & outputContainer);
    static void writeList(const QString & tagName, const QVariantList & list, QDomDocument & document, QDomNode &outputContainer);

    static void writeBool(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer);
    static void writeDouble(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer);
    static void writeInt(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer);
    static void writeString(const QString & tagName, const QString & value, QDomDocument & document, QDomNode &outputContainer);

    static QDomElement createElement(const QString & tagName, const QString & type, QDomDocument & document, QDomNode &outputContainer);


    static void readChildrenAsMap(const QDomNode & parentNode, QVariantMap & parentMap);
    static void readChildrenAsList(const QDomNode & parentNode, QVariantList & parentList);


};

#endif // SERIALIZER_H
