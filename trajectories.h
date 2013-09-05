#ifndef TRAJECTORIES_H
#define TRAJECTORIES_H

#include "model/store.h"
#include "bridge/embercppjslistener.h"

class Trajectories : public bridge::EmberCppJsListener {

    model::Store * store_;

public:
    Trajectories();
    ~Trajectories();

    void init();

    virtual void prepareCreateResponse(const std::string & type, QVariantMap & obj);
    virtual void prepareUpdateResponse(const std::string & type, QVariantMap & obj);

protected:

};

#endif // TRAJECTORIES_H
