#pragma once 

#include "novemberlib/interfaces/ITemplateSingleton.h"
#include "CGameRequestHandler.h"
#include "CInstanceManager.h"
#include "src/Objects/CSpawner.h"
#include "src/Objects/CObjectsCollection.h"
#include "src/Objects/CObjectsPool.h"

class CPlayer;
class CWorld : public ITemplateSingleton<CWorld>
{
public:
    virtual ~CWorld();
    
    const CGameRequestHandler& getRequestHandler() const 
    {
        return requestHandler;
    }
    const CInstanceManager& getInstanceManager() const 
    {
        return instanceManager;
    }
    const CSpawner& getSpawner() const 
    {
        return spawner;
    }
    const CObjectsCollection& getGlobalObjectsTable() const 
    {
        return globalObjectsTable;
    }
    const CObjectsPool<std::string, CPlayer>& getPlayersPool() const 
    {
        return players;
    }
    
    CGameRequestHandler& getRequestHandlerForModify() 
    {
        return requestHandler;
    }
    CInstanceManager& getInstanceManagerForModify() 
    {
        return instanceManager;
    }
    CSpawner& getSpawnerForModify() 
    {
        return spawner;
    }
    CObjectsCollection& getGlobalObjectsTableForModify() 
    {
        return globalObjectsTable;
    }
    CObjectsPool<std::string, CPlayer>& getPlayersPoolForModify() 
    {
        return players;
    }
    
    void run();
protected:
    CGameRequestHandler requestHandler;
    CInstanceManager    instanceManager;
    CSpawner            spawner;
    CObjectsCollection  globalObjectsTable;
    CObjectsPool<std::string, CPlayer> players;
     
    void logicLoop();
    void watchHandler();
    void init();
    void collectGarbage();
private:
    bool isInit;
    CWorld();    
    friend CWorld* ITemplateSingleton::getInstance();
};