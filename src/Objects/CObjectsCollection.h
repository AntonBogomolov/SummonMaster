#pragma once 

#include "CObjectsTable.h"

class CObjectsCollection
{
public:
    CObjectsCollection()
    {
        for ( int enumInt =  static_cast<int>(ENObjectsType::NOTSET); 
                  enumInt != static_cast<int>(ENObjectsType::CREATURE); ++enumInt)
        {
            ENObjectsType type = static_cast<ENObjectsType>(enumInt);
            tables[type] = new CObjectsTable(type);
        }
    }
    CObjectsCollection(const CObjectsCollection& coll) = delete;
    
    ~CObjectsCollection()
    {
        clear();
    }
    
    void clear()
    {
        for(auto it = tables.begin(); it != tables.end(); ++it)
        {
            delete it->second;
        }
        tables.clear();
    }
        
    void addObject(CObject* obj)
    {
        if(!obj) return;
        if(tables.find(obj->getObjectType()) == tables.end())
        {
            (tables[ENObjectsType::NOTSET])->addObject(obj);
        }
        else
        {
            (tables[obj->getObjectType()])->addObject(obj);
        }
    }
    void deleteObject(const unsigned int objId)
    {
        for(auto it = tables.begin(); it != tables.end(); ++it)
        {
            if( it->second->findObject(objId) != nullptr )
            {
                it->second->deleteObject(objId);
            }
        }
    }
    const CObject* findObject(const unsigned int objId) const
    {
        const CObject* result = nullptr;
        for(auto it = tables.begin(); it != tables.end(); ++it)
        {
            result = it->second->findObject(objId);
            if(result != nullptr) return result;
        }
        return nullptr;
    }    
    const CObject* getObject(const unsigned int objId) const
    {
        const CObject* result = nullptr;
        for(auto it = tables.begin(); it != tables.end(); ++it)
        {
            result = it->second->findObject(objId);
            if(result != nullptr) return result;
        }
        return nullptr;
    }
    CObject* getObjectForModify(const unsigned int objId)
    {
        CObject* result = nullptr;
        for(auto it = tables.begin(); it != tables.end(); ++it)
        {
            result = it->second->getObjectForModify(objId);
            if(result != nullptr) return result;
        }
        return nullptr;
    }
    const CObjectsTable* getObjectsTableByType(const ENObjectsType type) const
    {
        if(tables.find(type) == tables.end())
        {
            return nullptr;
        }
        else
        {
            return (tables.at(type));
        }
    }
    CObjectsTable* getObjectsTableByType(const ENObjectsType type)
    {
        if(tables.find(type) == tables.end())
        {
            return nullptr;
        }
        else
        {
            return (tables[type]);
        }
    }
    
private:  
    std::map<ENObjectsType, CObjectsTable*> tables;
};