#ifndef EMBERCPPJSLISTENER_H
#define EMBERCPPJSLISTENER_H

#include "cppjavascriptbridge.h"
#include "../model/tobject.h"
#include "../model/store.h"

namespace bridge {

    class EmberCppJsListener : public CppJavascriptBridgeListener {
        model::Store * store_;

    public:
        EmberCppJsListener();
        ~EmberCppJsListener();

        void setModel(const model::TObjectModelMap & model);


        virtual void processCall(int op, int opId, QVariantMap & data);

        void object2qvariant(const model::TObjectModel * model, const model::TObjectPtr obj, QVariantMap & result);
        void updateObject(const model::TObjectModel * model, model::TObjectPtr obj, QVariantMap & data);
        model::TObjectPtr createObject(const std::string & type, const model::TObjectModelParams & model, QVariantMap & data);

        virtual bool objectCreated(model::TObjectPtr obj);
        virtual void prepareCreateResponse(const std::string & type, QVariantMap & obj);

        virtual bool objectUpdated(model::TObjectPtr obj);
        virtual void prepareUpdateResponse(const std::string & type, QVariantMap & obj);

        virtual void objectWillBeDeleted(const std::string & type, const model::TObjectId & id);

    };

}

#endif // EMBERCPPJSLISTENER_H
