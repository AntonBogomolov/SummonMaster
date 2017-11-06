#pragma once 

#include "novemberlib/interfaces/ITemplateSingleton.h"
#include "CGameRequestHandler.h"
#include "CInstanceManager.h"

class CWorld : public ITemplateSingleton<CWorld>
{
public:
    virtual ~CWorld();
    
    CGameRequestHandler& getRequestHandler() 
    {
        return requestHandler;
    }
    CInstanceManager& getInstanceManager() 
    {
        return instanceManager;
    }
protected:
    CGameRequestHandler requestHandler;
    CInstanceManager    instanceManager;
private:
    CWorld();    
    friend CWorld* ITemplateSingleton::getInstance();
};