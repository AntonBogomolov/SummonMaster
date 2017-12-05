#pragma once 

#include "CObject.h"
#include "CObjectsPool.h"
#include "src/World/CInstance.h"
#include "src/Creatures/CPlayer.h"

class CMap;
class CSpawner
{
public:
    template<class T> CObject* createObject(CObjectsPool<unsigned int, CObject>& objectPool, const CObjectCreationParams& params) const
    {
        CObject* result = nullptr; 
        try
        {
            result = new T(params);
            objectPool.addToPool(result->getObjectId(), result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CInstance* createInstance(const CInstanceCreationParams& params) const 
    {
        CInstance* result = nullptr; 
        try
        {
            result = new T(params);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CPlayer* createPlayer(CObjectsPool<std::string, CPlayer>& playersPool,
                                            const CPlayerCreationParams& params) const 
    {
        CPlayer* result = nullptr; 
        try
        {
            result = new T(params);
            playersPool.addToPool(result->getKey(), result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CMapObject* spawnMapObject(CMap& map, const CMapObjectCreationParam& params, 
                                                 CObject* object) const 
    {
        CMapObject* result = nullptr;
        try
        {
            result = new T(params, &map, object, false);
            map.getObjectsOnMapCollectionForModify().getObjectsPoolForModify().addToPool(result->getInstanceId(), result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CMapObject* spawnInstanceMapObject(CMap& map, const CMapObjectCreationParam& params, 
                                                         CObject* object) const
    {
        CMapObject* result = nullptr;
        try
        {
            result = new T(params, &map, object, true);
            map.getObjectsOnMapCollectionForModify().getObjectsPoolForModify().addToPool(result->getInstanceId(), result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }

    CSpawner()
    {
        
    }
    virtual ~CSpawner()
    {
        
    }
protected:
};
