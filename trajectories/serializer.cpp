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

#include "serializer.h"
#include <QFile>

#include <iostream>


void Serializer::save(QFile & file, const QString & rootElementTagName, const QVariantMap &data) {
    QDomDocument doc = write(rootElementTagName, data);

    file.open(QFile::WriteOnly);
    file.write(doc.toByteArray());
    file.close();
}

QVariantMap Serializer::load(QFile & file) {
    QDomDocument doc;

    file.open(QFile::ReadOnly);
    QByteArray xml = file.readAll();
    file.close();

    doc.setContent(xml);
    return read(doc);
}


QDomDocument Serializer::write(const QString & rootElementTagName, const QVariantMap & map) {
    QDomDocument doc;
    writeMap(rootElementTagName, map, doc, doc);
    return doc;
}

void Serializer::writeValue(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer) {
    switch(value.type()) {
    case QMetaType::QVariantMap:
        writeMap(tagName, value.toMap(), document, outputContainer);
        break;
    case QMetaType::QVariantList:
        writeList(tagName, value.toList(), document, outputContainer);
        break;
    case QMetaType::Bool:
        writeBool(tagName, value, document, outputContainer);
        break;
    case QMetaType::Double:
        writeDouble(tagName, value, document, outputContainer);
        break;
    case QMetaType::Int:
        writeInt(tagName, value, document, outputContainer);
        break;
    case QMetaType::QString:
        writeString(tagName, value.toString(), document, outputContainer);
        break;
    default:
        std::cout << "unknown type: " << value.type() << std::endl;
    }
}

void Serializer::writeMap(const QString & tagName, const QVariantMap & map, QDomDocument & document, QDomNode &outputContainer) {
    QDomElement element = createElement(tagName, "map", document, outputContainer);

    for(QVariantMap::const_iterator it = map.begin(); it != map.end(); it++) {
        writeValue(it.key(), it.value(), document, element);
    }

}

void Serializer::writeList(const QString & tagName, const QVariantList & list, QDomDocument & document, QDomNode &outputContainer) {
    QDomElement element = createElement(tagName, "list", document, outputContainer);

    for(QVariantList::const_iterator it = list.begin(); it!=list.end(); it++) {
        writeValue("item", *it, document, element);
    }
}

QDomElement Serializer::createElement(const QString & tagName, const QString & type, QDomDocument & document, QDomNode &outputContainer) {
    QDomElement element = document.createElement(tagName);
    outputContainer.appendChild(element);
    element.setAttribute("type", type);
    return element;
}

void Serializer::writeBool(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer) {
    QDomElement element = createElement(tagName, "bool", document, outputContainer);
    QDomText textElement = document.createTextNode(value.toString());
    element.appendChild(textElement);
}
void Serializer::writeDouble(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer) {
    bool ok;
    value.toDouble(&ok);
    if (ok) {
        QDomElement element = createElement(tagName, "double", document, outputContainer);
        QDomText textElement = document.createTextNode(value.toString());
        element.appendChild(textElement);
    }
}
void Serializer::writeInt(const QString & tagName, const QVariant & value, QDomDocument & document, QDomNode &outputContainer) {
    bool ok;
    value.toInt(&ok);
    if (ok) {
        QDomElement element = createElement(tagName, "int", document, outputContainer);
        QDomText textElement = document.createTextNode(value.toString());
        element.appendChild(textElement);
    }
}

void Serializer::writeString(const QString & tagName, const QString & value, QDomDocument & document, QDomNode &outputContainer) {
    QDomElement element = createElement(tagName, "string", document, outputContainer);
    QDomText textElement = document.createTextNode(value);
    element.appendChild(textElement);
}



QVariantMap Serializer::read(const QDomDocument & doc) {
    QDomElement root = doc.documentElement();
    QVariantMap map;
    readChildrenAsMap(root, map);

    return map;
}

void Serializer::readChildrenAsMap(const QDomNode & parentNode, QVariantMap & parentMap) {
    QDomNodeList list = parentNode.childNodes();
    for (int i = 0; i < list.count(); i++) {
        QDomNode node = list.at(i);
        if (node.isElement()) {
            QDomElement element = node.toElement();

            QString type = element.attribute("type", "");
            QString tag = element.tagName();
            if (type == "int") {
                parentMap[tag] = element.text().toInt();
            } else if (type == "bool") {
                parentMap[tag] = element.text() == "true";
            } else if (type == "double") {
                parentMap[tag] = element.text().toDouble();
            } else if (type == "string") {
                parentMap[tag] = element.text();
            } else if (type == "map") {
                QVariantMap map;
                readChildrenAsMap(element, map);
                parentMap[tag] = map;
            } else if (type == "list") {
                QVariantList list;
                readChildrenAsList(element, list);
                parentMap[tag] = list;
            }
        }
    }
}

void Serializer::readChildrenAsList(const QDomNode & parentNode, QVariantList & parentList) {
    QDomNodeList list = parentNode.childNodes();
    for (int i = 0; i < list.count(); i++) {
        QDomNode node = list.at(i);
        if (node.isElement()) {
            QDomElement element = node.toElement();

            QString type = element.attribute("type", "");
            QString tag = element.tagName();
            if (type == "int") {
                parentList.append(element.text().toInt());
            } else if (type == "bool") {
                parentList.append(element.text() == "true");
            } else if (type == "double") {
                parentList.append(element.text().toDouble());
            } else if (type == "string") {
                parentList.append(element.text());
            } else if (type == "map") {
                QVariantMap map;
                readChildrenAsMap(element, map);
                parentList.append(map);
            } else if (type == "list") {
                QVariantList list;
                readChildrenAsList(element, list);
                parentList.append(list);
            }
        }
    }
}
