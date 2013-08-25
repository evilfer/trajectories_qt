#include "trajectories.h"

#include "simulator/ephemerides/spiceposition.h"
#include "model/store.h"
#include "bridge/cppjavascriptbridge.h"


Trajectories::Trajectories(): store_(NULL) {
    this->init();
}

Trajectories::~Trajectories() {
    if (this->store_) {
        delete this->store_;
    }
}

void Trajectories::processCall(int op, int opId, QVariantMap & data) {
    std::string type = data["type"].toString().toStdString();
    const model::TObjectModel * model = this->store_->getModel(type);

    if (model) {
        switch (op) {
        case BRIDGE_FIND:
        {
            QVariantMap qobj;
            model::TObjectPtr obj = this->store_->find(type, data["id"].toString().toStdString());
            this->object2qvariant(model, obj, qobj);
            QVariantMap result;
            result[type.c_str()] = qobj;
            this->makeCall(opId, true, result);
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

            QVariantMap result;
            result[model->plural] = qlist;

            this->makeCall(opId, true, result);
            break;
        }
        case BRIDGE_CREATE:
        {
            QVariantMap record = data["record"].toMap();

            model::TObjectPtr obj = new model::TObject();
            obj->setId(record["id"].toString().toStdString());
            obj->setType(type);

            this->updateObject(model, obj, record);
            this->store_->add(obj);

            this->makeCall(opId, true, record);
            break;
        }
        case BRIDGE_UPDATE:
        {
            QVariantMap record = data["record"].toMap();
            model::TObjectPtr obj = this->store_->find(type, record["id"].toString().toStdString());
            this->updateObject(model, obj, record);
            this->store_->updated(obj);
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

QVariantMap Trajectories::processSyncCall(int op, QVariantMap & data) {
    QVariantMap output;

    if (op == BRIDGE_NEWID) {
        std::string type = data["type"].toString().toStdString();
        output["id"] = this->store_->newId(type).c_str();
    }

    return output;
}


void Trajectories::init() {

    ephemerides::SpicePosition::init();

    model::TObjectModelMap model = {
        {
            "simulation", {
                true,
                "simulations",
                {},
                {
                    {"metadata", {true, false, "simulation_metadata", "metadata", "metadata_key"}}
                },
                {}
            }
        },
        {
            "simulation_metadata", {
                true,
                "simulation_metadatas",
                {
                    {"title", TOBJECT_PARAM_STRING},
                    {"description", TOBJECT_PARAM_STRING}
                },
                {
                    {"simulation", {false, false, "simulation", "simulation", "simulation_type"}}
                },
                {}
            }
        }
    };

    this->store_ = new model::Store(model);
}

void Trajectories::object2qvariant(const model::TObjectModel * model, const model::TObjectPtr obj, QVariantMap & result) {
    result.insert("id", obj->id().c_str());

    for (model::TObjectModelParams::const_iterator i = model->params.begin(); i != model->params.end(); i++) {
        switch(i->second) {
        case TOBJECT_PARAM_INT:
            if (!obj->emptyInt(i->first)) {
                result.insert(i->first.c_str(), obj->pInt(i->first));
            }
            break;
        case TOBJECT_PARAM_DOUBLE:
            if (!obj->emptyDouble(i->first)) {
                result.insert(i->first.c_str(), obj->pDouble(i->first));
            }
            break;
        case TOBJECT_PARAM_STRING:
            if (!obj->emptyString(i->first)) {
                result.insert(i->first.c_str(), obj->pString(i->first).c_str());
            }
            break;
        }
    }

    for (model::TObjectModelLinkParams::const_iterator i = model->links.begin(); i != model->links.end(); i++) {
        if (!obj->emptyLink(i->first)) {
            const model::TObjectLink * link = obj->pLink(i->first);
            result.insert(i->second.id_key, link->objid().c_str());
            if (i->second.polymorphic) {
                result.insert(i->second.type_key, link->type().c_str());
            }
        }
    }

    /* TODO arrays */

}

void Trajectories::updateObject(const model::TObjectModel * model, model::TObjectPtr obj, QVariantMap & data) {
    for (model::TObjectModelParams::const_iterator i = model->params.begin(); i != model->params.end(); i++) {
        switch(i->second) {
        case TOBJECT_PARAM_INT:
            if (data.contains(i->first.c_str())) {
                obj->pInt(i->first, data[i->first.c_str()].toInt());
            } else {
                obj->clearInt(i->first);
            }
            break;
        case TOBJECT_PARAM_DOUBLE:
            if (data.contains(i->first.c_str())) {
                obj->pDouble(i->first, data[i->first.c_str()].toDouble());
            } else {
                obj->clearDouble(i->first);
            }
            break;
        case TOBJECT_PARAM_STRING:
            if (data.contains(i->first.c_str())) {
                obj->pString(i->first, data[i->first.c_str()].toString().toStdString());
            } else {
                obj->clearString(i->first);
            }
            break;
        }
    }

    for (model::TObjectModelLinkParams::const_iterator i = model->links.begin(); i != model->links.end(); i++) {
        if (data.contains(i->second.id_key)) {
            model::TObjectId id = data[i->second.id_key].toString().toStdString();
            std::string type = i->second.polymorphic ? data[i->second.type_key].toString().toStdString() : i->second.type;
            obj->pLink(i->first, type, id);
        } else {
            obj->clearLink(i->first);
        }
    }

    /* TODO arrays */
}

