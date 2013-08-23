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
            QVariantMap result;
            model::TObjectPtr obj = this->store_->find(type, data["id"].toInt());
            this->object2qvariant(model->params, obj, result);
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
                this->object2qvariant(model->params, *i, qobj);
                qlist.append(qobj);
            }

            QVariantMap result;
            result["list"] = QVariantList();

            this->makeCall(opId, true, result);
            break;
        }
        case BRIDGE_CREATE:
        {
            QVariantMap record = data["record"].toMap();

            model::TObjectPtr obj = new model::TObject();
            obj->setId(record["id"].toInt());
            obj->setType(type);

            this->updateObject(model->params, obj, record);
            this->store_->add(obj);

            this->makeCall(opId, true, record);
            break;
        }
        case BRIDGE_UPDATE:
        {
            QVariantMap record = data["record"].toMap();
            //model::TObjectPtr obj = this->store_->find()
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
        int id = this->store_->newId(type);
        output["id"] = id;
    }

    return output;
}


void Trajectories::init() {

    ephemerides::SpicePosition::init();

    model::TObjectModelMap model = {
        {
            "Simulation",
            {
                true,
                {
                    {"metadata", TOBJECT_PARAM_OWNEDLINK}
                }
            }
        },
        {
            "SimulationMetadata",
            {
                true,
                {
                    {"title", TOBJECT_PARAM_STRING},
                    {"description", TOBJECT_PARAM_STRING},
                    {"simulation", TOBJECT_PARAM_LINK}
                }
            }
        }
    };

    this->store_ = new model::Store(model);
}

void Trajectories::object2qvariant(const model::TObjectModelParams & model, const model::TObjectPtr obj, QVariantMap & result) {
    for (model::TObjectModelParams::const_iterator i = model.begin(); i != model.end(); i++) {
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
        case TOBJECT_PARAM_LINK:
            if (!obj->emptyLink(i->first)) {
                result.insert(i->first.c_str(), obj->pLink(i->first)->objid());
            }
            break;
        }
    }
}

void Trajectories::updateObject(const model::TObjectModelParams & model, model::TObjectPtr obj, QVariantMap & data) {
    for (model::TObjectModelParams::const_iterator i = model.begin(); i != model.end(); i++) {
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
        case TOBJECT_PARAM_LINK:
            if (data.contains(i->first.c_str())) {
                /* TODO */
            } else {
                obj->clearLink(i->first);
            }
            break;
        }
    }
}

