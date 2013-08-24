#ifndef TRAJECTORIES_H
#define TRAJECTORIES_H

#include "model/store.h"
#include "bridge/cppjavascriptbridgelistener.h"

class Trajectories : public bridge::CppJavascriptBridgeListener {

    model::Store * store_;

public:
    Trajectories();
    ~Trajectories();

    void init();

protected:
    virtual void processCall(int op, int opId, QVariantMap & data);
    virtual QVariantMap processSyncCall(int op, QVariantMap & data);

    void object2qvariant(const model::TObjectModel * model, const model::TObjectPtr obj, QVariantMap & result);
    void updateObject(const model::TObjectModel * model, model::TObjectPtr obj, QVariantMap & data);
    model::TObjectPtr createObject(const std::string & type, const model::TObjectModelParams & model, QVariantMap & data);
};

#endif // TRAJECTORIES_H
