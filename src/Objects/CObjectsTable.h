#pragma once 

#include "CObject.h"
#include <unordered_map>

using namespace std;

namespace std 
{
    template <>
    class hash<ENObjectsType>
    {
    public :
        size_t operator()(const ENObjectsType &type ) const
        {
            return static_cast<int>(type);
        }
    };
}

class CObjectsTable
{
public:
    CObjectsTable(const ENObjectsType type) : type(type)
    {
    }
    ~CObjectsTable()
    {
        clear();
    }
    
    const ENObjectsType getType() const
    {
        return type;
    }
    void clear()
    {
        for(auto it = table.begin(); it!= table.end(); ++it)
        {
            CObject* currObj = it->second;
            delete currObj;
        }
        table.clear();
    }
        
    void addObject(CObject* obj)
    {
        if(!obj) return;
        if(table.find(obj->getObjectId()) == table.end())
        {
            if(type == ENObjectsType::NOTSET || type == obj->getObjectType()) 
            {
                table[obj->getObjectId()] = obj;
            }
        }
    }
    void deleteObject(const unsigned int objId)
    {
        auto it = table.find(objId);
        if(it != table.end())
        {
            delete table[objId];
            table.erase(it);
        }
    }
    const CObject* findObject(const unsigned int objId) const
    {
        auto it = table.find(objId);
        if(it != table.end())
        {
            return table.at(objId);
        }
        return nullptr;
    }    
    const CObject* getObject(const unsigned int objId) const
    {
        auto it = table.find(objId);
        if(it != table.end())
        {
            return table.at(objId);
        }
        return nullptr;
    }
    CObject* getObjectForModify(const unsigned int objId)
    {
        auto it = table.find(objId);
        if(it != table.end())
        {
            return table[objId];
        }
        return nullptr;
    }
    
protected:
    std::unordered_map<unsigned int, CObject*> table;
    ENObjectsType type;
};