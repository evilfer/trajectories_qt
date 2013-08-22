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
    virtual QVariantMap processCall(int op, int opId, QVariantMap & data);

    void object2qvariant(const model::TObjectModelParams & model, const model::TObjectPtr obj, QVariantMap & result);
    void updateObject(const model::TObjectModelParams & model, model::TObjectPtr obj, QVariantMap & data);
    model::TObjectPtr createObject(const std::string & type, const model::TObjectModelParams & model, QVariantMap & data);
};

#endif // TRAJECTORIES_H
