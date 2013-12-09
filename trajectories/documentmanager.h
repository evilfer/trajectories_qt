#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QVariantMap>

class DocumentManager {
public:

    static void listDocuments(QVariantMap & data, QVariantMap & result);
    static void saveDocument(QVariantMap & data, QVariantMap & result);
    static void loadDocument(QVariantMap &data, QVariantMap &result);
};

#endif // DOCUMENTMANAGER_H
