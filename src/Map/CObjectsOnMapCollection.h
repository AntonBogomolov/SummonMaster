#pragma once 

#include "CMapObject.h"
#include "src/Objects/CObjectsPool.h"

#include <vector>
#include <unordered_map>


class CObjectsOnMapCollection
{
public:
    CObjectsOnMapCollection()
    {
        
    }
    ~CObjectsOnMapCollection()
    {
        
    }
    CObjectsOnMapCollection(const CObjectsOnMapCollection& coll) = delete;
    
    CObjectsPool<unsigned int, CMapObject>& getObjectsPoolForModify()
    {
        return objectPool;
    }
    const CObjectsPool<unsigned int, CMapObject>& getObjectsPool() const
    {
        return objectPool;
    }
    void collectGarbage()
    {
        std::unordered_map<unsigned int, CMapObject*>& mapObjects = objectPool.getObjectsForModify();
        for(auto it = mapObjects.begin(); it != mapObjects.end();)
        {
            CMapObject* currObj = it->second;
            if(!isConsistMapObject(currObj))
            {
                delete currObj;
                mapObjects.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    CMapObject* getMapObject(const CCellCoords& cell, const unsigned int objInstanceId)
    {
        if(objects.find(cell) == objects.end()) return nullptr;
        
        std::vector<CMapObject*>& objVector = objects[cell];
        for(auto it = objVector.begin(); it != objVector.end(); ++it)
        {
            CMapObject* currObj = (*it);
            if(currObj->getInstanceId() == objInstanceId) return currObj;
        }
        return nullptr;
    }
    bool removeMapObject(const CCellCoords& cell, const unsigned int objInstanceId)
    {
        if(objects.find(cell) == objects.end()) return false;
        
        std::vector<CMapObject*>& objVector = objects[cell];
        for(auto it = objVector.begin(); it != objVector.end();)
        {
            CMapObject* currObj = (*it);
            if(currObj->getInstanceId() == objInstanceId)
            {
                objVector.erase(it);
                objectPool.deleteObject(currObj);
                return true;
            }
            else
            {
                ++it;
            }
        }
        return false;
    }  
    bool getIsConsistBlockingObject(const CCellCoords& cell)
    {
        if(objects.find(cell) == objects.end()) return false;
        
        std::vector<CMapObject*>& objVector = objects[cell];
        for(auto it = objVector.begin(); it != objVector.end(); ++it)
        {
            CMapObject* currObj = (*it);
            if(currObj->getBlockMode() != ENMapObjectBlockMode::notBlock) return true;
        }
        return false;
    }    
    bool isConsistMapObject(const CCellCoords& cell, CMapObject* obj)
    {
        return isConsistMapObject(cell, obj->getInstanceId());
    }
    bool isConsistMapObject(const CCellCoords& cell, const unsigned int objInstanceId)
    {
        return getMapObject(cell, objInstanceId) != nullptr;
    }
    bool isConsistMapObject(CMapObject* obj)
    {
        for(auto it = objects.begin(); it != objects.end(); ++it)
        {
            if(isConsistMapObject(it->first, obj)) return true;            
        }
        return false;
    }
    void removeMapObject(CMapObject* obj)
    {
        for(auto it = objects.begin(); it != objects.end(); ++it)
        {
            if(removeMapObject(it->first, obj->getInstanceId())) 
            {
                return;
            }
        }
    }
    void removeMapObject(const CCellCoords& cell, CMapObject* obj)
    {
        removeMapObject(cell, obj->getInstanceId());
    }
    bool placeMapObject(CMapObject* obj, const CCellCoords& coordsToPlace)
    {
        if(!obj || !obj->isValid()) return false;
        
        if(objects.find(coordsToPlace) == objects.end())
        {
            objects[coordsToPlace] = std::vector<CMapObject*>();
        }
        objects[coordsToPlace].push_back(obj);
        return true;
    }
    std::vector<CMapObject*>& getAllMapObjectInCell(const CCellCoords& cell)
    {
        if(objects.find(cell) == objects.end()) return objects[CCellCoords(0,0)];
        
        return objects[cell];
    }    
    bool moveObjectToCell(CMapObject* obj, const CCellCoords& src, const CCellCoords& dest)
    {
        if(!obj || !obj->isValid()) return false;
        
        if(objects.find(src) == objects.end()) return false;
    
        std::vector<CMapObject*>& objVector = objects[src];
        for(auto it = objVector.begin(); it != objVector.end(); ++it)
        {
            CMapObject* currObj = (*it);
            if(currObj->getInstanceId() == obj->getInstanceId()) 
            {
                if(it == objects[src].end()) return false;
                if(placeMapObject(obj, dest))
                {
                    objects[src].erase(it);
                    return true;
                }
                return false;
            }
        }
        return false;
    }
protected:
    std::unordered_map<CCellCoords, std::vector<CMapObject*>> objects;
    CObjectsPool<unsigned int ,CMapObject> objectPool;
};