#include "embercppjslistener.h"

namespace bridge {


    EmberCppJsListener::EmberCppJsListener() : store_(NULL) {
    }



    EmberCppJsListener::~EmberCppJsListener() {
        if (this->store_) {
            delete this->store_;
        }
    }

    void EmberCppJsListener::setModel(const model::TObjectModelMap & model) {
        if (this->store_) {
            delete this->store_;
        }
        this->store_ = new model::Store(model);
    }


    void EmberCppJsListener::processCall(int op, int opId, QVariantMap & data) {
        std::string type = data["type"].toString().toStdString();
        const model::TObjectModel * model = this->store_->getModel(type);

        if (model) {
            switch (op) {
            case BRIDGE_FIND:
            {
                QVariantMap qobj;
                std::string id = data["id"].toString().toStdString();
                model::TObjectPtr obj = this->store_->find(type, id);
                bool wasUpdated = false;

                if (!obj && id == "singleton") {
                    obj = new model::TObject();
                    obj->setType(type);
                    obj->setId(id);

                    const model::TObjectModelLinkParams & links = model->links;
                    for(model::TObjectModelLinkParams::const_iterator i = links.begin(); i != links.end(); i++) {
                        if (i->second.toSingleton) {
                            obj->setLink(i->first, i->second.type, "singleton");
                        }
                    }
                    this->store_->add(obj);
                    this->objectCreated(obj);
                    wasUpdated = true;
                }

                this->object2qvariant(model, obj, qobj);

                if (wasUpdated) {
                    this->prepareCreateResponse(type, qobj);
                }

                this->makeCall(opId, true, qobj);
                break;
            }
            case BRIDGE_FINDALL:
            {
                model::TObjectList list;
                this->store_->findAll(type, list);
                QVariantList qlist;
                for(model::TObjectList::iterator i = list.begin(); i != list.end(); i++) {
                    QVariantMap qobj;
                    this->object2qvariant(model, *i, qobj);
                    qlist.append(qobj);
                }

                this->makeCall(opId, true, qlist);
                break;
            }
            case BRIDGE_CREATE:
            {
                QVariantMap record = data["record"].toMap();
                model::TObjectPtr obj = new model::TObject();
                this->updateObject(model, obj, record);
                obj->setType(type);
                obj->setId(this->store_->newId(type));
                record["id"] = obj->id().c_str();

                this->store_->add(obj);

                if (this->objectCreated(obj)) {
                    this->object2qvariant(model, obj, record);
                }
                this->prepareCreateResponse(type, record);

                this->makeCall(opId, true, record);

                break;
            }
            case BRIDGE_UPDATE:
            {
                QVariantMap record = data["record"].toMap();
                model::TObjectPtr obj = this->store_->find(type, record["id"].toString().toStdString());
                this->updateObject(model, obj, record);
                this->store_->updated(obj);

                if (this->objectUpdated(obj)) {
                    this->object2qvariant(model, obj, record);
                }
                this->prepareUpdateResponse(type, record);


                this->makeCall(opId, true, record);
                break;
            }
            case BRIDGE_DELETE:
            {
                break;
            }
            default:
            {
                QVariantMap empty;
                this->makeCall(opId, true, empty);
                break;
            }
            }
        }
    }

    void EmberCppJsListener::object2qvariant(const model::TObjectModel * model, const model::TObjectPtr obj, QVariantMap & result) {
        result.insert("id", obj->id().c_str());

        for (model::TObjectModelParams::const_iterator i = model->params.begin(); i != model->params.end(); i++) {
            switch(i->second) {
            case TOBJECT_PARAM_INT:
                if (!obj->emptyInt(i->first)) {
                    result.insert(i->first.c_str(), obj->getInt(i->first));
                }
                break;
            case TOBJECT_PARAM_DOUBLE:
                if (!obj->emptyDouble(i->first)) {
                    result.insert(i->first.c_str(), obj->getDouble(i->first));
                }
                break;
            case TOBJECT_PARAM_STRING:
                if (!obj->emptyString(i->first)) {
                    result.insert(i->first.c_str(), obj->getString(i->first).c_str());
                }
                break;
            }
        }

        for (model::TObjectModelLinkParams::const_iterator i = model->links.begin(); i != model->links.end(); i++) {
            if (!obj->emptyLink(i->first)) {
                const model::TObjectLink * link = obj->getLink(i->first);
                result.insert(i->second.id_key, link->objid().c_str());
                if (i->second.polymorphic) {
                    result.insert(i->second.type_key, link->type().c_str());
                }
            }
        }

        /* TODO arrays */

    }

    void EmberCppJsListener::updateObject(const model::TObjectModel * model, model::TObjectPtr obj, QVariantMap & data) {
        for (model::TObjectModelParams::const_iterator i = model->params.begin(); i != model->params.end(); i++) {
            const char * key = i->first.c_str();
            switch(i->second) {
            case TOBJECT_PARAM_INT:
                if (data.contains(key) && data[key].toString().length() > 0) {
                    obj->setInt(i->first, data[key].toInt());
                } else {
                    obj->clearInt(i->first);
                }
                break;
            case TOBJECT_PARAM_DOUBLE:
                if (data.contains(key) && data[key].toString().length() > 0) {
                    obj->setDouble(i->first, data[key].toDouble());
                } else {
                    obj->clearDouble(i->first);
                }
                break;
            case TOBJECT_PARAM_STRING:
                if (data.contains(key)) {
                    obj->setString(i->first, data[key].toString().toStdString());
                } else {
                    obj->clearString(i->first);
                }
                break;
            }
        }

        for (model::TObjectModelLinkParams::const_iterator i = model->links.begin(); i != model->links.end(); i++) {
            if (data.contains(i->second.id_key) && data[i->second.id_key].toString().size() > 0) {
                model::TObjectId id = data[i->second.id_key].toString().toStdString();
                std::string type = i->second.polymorphic ? data[i->second.type_key].toString().toStdString() : i->second.type;
                obj->setLink(i->first, type, id);
            } else {
                obj->clearLink(i->first);
            }
        }

        /* TODO arrays */
    }

    bool EmberCppJsListener::objectCreated(model::TObjectPtr) {return false;}
    void EmberCppJsListener::prepareCreateResponse(const std::string &, QVariantMap &) {}

    bool EmberCppJsListener::objectUpdated(model::TObjectPtr) {return false;}
    void EmberCppJsListener::prepareUpdateResponse(const std::string &, QVariantMap &) {}

    void EmberCppJsListener::objectWillBeDeleted(const std::string &, const model::TObjectId &) {}

}
