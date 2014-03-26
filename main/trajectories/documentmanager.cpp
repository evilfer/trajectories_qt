#include "documentmanager.h"

#include <QTextStream>
#include <QDirIterator>
#include <qjson/parser.h>


void DocumentManager::listDocuments(QVariantMap &, QVariantMap & result) {
    QJson::Parser parser;

    QDirIterator dirIt("../simulations");

    QVariantMap list;

    while (dirIt.hasNext()) {
        dirIt.next();
        QFileInfo info = QFileInfo(dirIt.filePath());
        if (info.isFile() && info.suffix() == "json") {
            QFile file(dirIt.filePath());
            if (file.open(QFile::ReadOnly | QFile::Text)) {
                QString id = info.baseName();
                QTextStream in(&file);
                QString content = in.readAll();
                file.close();

                bool ok;
                QVariantMap sim = parser.parse(content.toUtf8(), &ok).toMap();
                if (ok) {
                    list[id] = sim["metadata"].toMap();
                }
            }
        }
    }

    result["documents"] = list;
}

void DocumentManager::loadDocument(QVariantMap &data, QVariantMap &result) {
    bool ok = false;
    QString problem;

    if (!data.contains("id")) {
        problem = "no-id";
    } else {
        QString id = data["id"].toString();
        QString fileName = QString("../simulations") + id + QString(".json");
        QFile file(fileName);
        if (!file.exists()) {
            problem = "no-file";
        } else if (!file.open(QFile::ReadOnly | QFile::Text)) {
            problem = "cant-read";
        } else {
            QTextStream in(&file);
            QString content = in.readAll();
            file.close();

            QJson::Parser parser;
            bool ok;
            QVariantMap sim = parser.parse(content.toUtf8(), &ok).toMap();

            if (ok) {
                result["document"] = sim;
            } else {
                problem = "bad-file";
            }
        }
    }

    result["ok"] = ok;
    if (!ok) {
        result["problem"] = problem;
    }
}

void DocumentManager::saveDocument(QVariantMap &data, QVariantMap &result) {
    bool ok = false;
    QString problem;

    if (!data.contains("id")) {
        problem = "no-id";
    } else {
        QString id = data["id"].toString();
        QString fileName = QString("../simulations/") + id + QString(".json");
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            problem = "cant-write";
        } else {
            QTextStream stream(&file);
            stream << data["document"].toString();
            file.close();
            ok = true;
        }
    }

    result["ok"] = ok;
    if (!ok) {
        result["problem"] = problem;
    }
}
