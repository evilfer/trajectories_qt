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
    virtual void processCall(int op, QVariantMap & data);
};

#endif // TRAJECTORIES_H
