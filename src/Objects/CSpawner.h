#pragma once 

#include "CObject.h"
#include "CObjectsPool.h"
#include "src/World/CInstance.h"

class CMap;
class CSpawner
{
public:
    template<class T> CObject* createObject(CObjectsPool<CObject>& objectPool, const CObjectCreationParams& params)
    {
        CObject* result = nullptr; 
        try
        {
            result = new T(params);
            objectPool.addToPool(result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CInstance* createInstance(const CInstanceCreationParams& params)
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
    
    template<class T> CMapObject* spawnMapObject(CMap& map, const CMapObjectCreationParam& params, CObject* object)
    {
        CMapObject* result = nullptr;
        try
        {
            result = new T(params, object, false);
            map.getObjectsOnMapCollection().getObjectsPool().addToPool(result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CMapObject* spawnInstanceMapObject(CMap& map, const CMapObjectCreationParam& params, CObject* object)
    {
        CMapObject* result = nullptr;
        try
        {
            result = new T(params, object, true);
            map.getObjectsOnMapCollection().getObjectsPool().addToPool(result);
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