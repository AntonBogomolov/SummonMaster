#pragma once 

#include <novemberlib/interfaces/ITemplateSingleton.h>
#include "CObject.h"
#include "CMapObject.h"

class CMap;
class CSpawner : public ITemplateSingleton
{
public:
    template<class T> CObject* createObject(CObjectsPool& objectPool, const CObjectCreationParams& params)
    {
        CObject* result = nullptr; 
        try
        {
            result = new T(params);
            objectPool->addToPool(result);
        }
        catch(...)
        {
            result = nullptr;
        }            
        return result;
    }
    
    template<class T> CMap* createMap(const CObjectCreationParams& params)
    {
        CMap* result = nullptr; 
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

    ~virtual CSpawner()
    {
        
    }
protected:
private:
    friend CSpawner* ITemplateSingleton::getInstance();
    CSpawner()
    {
        
    }
};