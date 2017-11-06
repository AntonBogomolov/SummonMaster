#pragma once 

#include "novemberlib/interfaces/ITemplateSingleton.h"
#include "CGameRequestHandler.h"
#include "CInstanceManager.h"
#include "src/Objects/CSpawner.h"

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
    CSpawner& getSpawner() 
    {
        return spawner;
    }
protected:
    CGameRequestHandler requestHandler;
    CInstanceManager    instanceManager;
    CSpawner            spawner;
private:
    CWorld();    
    friend CWorld* ITemplateSingleton::getInstance();
};