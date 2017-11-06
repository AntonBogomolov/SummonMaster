#pragma once 

#include "novemberlib/interfaces/ITemplateSingleton.h"
#include "CGameRequestHandler.h"
#include "CInstanceManager.h"
#include "src/Objects/CSpawner.h"
#include "src/Objects/CObjectsCollection.h"

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
    CObjectsCollection& getGlobalObjectsTable() 
    {
        return globalObjectsTable;
    }
   
    void run();
protected:
    CGameRequestHandler requestHandler;
    CInstanceManager    instanceManager;
    CSpawner            spawner;
    CObjectsCollection  globalObjectsTable;
     
    void logicLoop();
    void watchHandler();
    void init();
    void collectGarbage();
private:
    bool isInit;
    CWorld();    
    friend CWorld* ITemplateSingleton::getInstance();
};