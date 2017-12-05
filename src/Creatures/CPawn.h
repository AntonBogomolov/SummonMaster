#pragma once 

#include "src/IJSONSerializable.h"
#include "src/IDBSerializable.h"
#include "src/IUpdatable.h"
#include "src/Objects/CObjectsPool.h"
#include "src/Map/CMap.h"
#include "src/Creatures/CCreature.h"

#include <string>

class CPawnCreationParams : public CObjectCreationParams
{
public:
    CPawnCreationParams(const ENObjectsType type, const CCreatureCreationParams& templateCreature, const std::string& name) 
                        : CObjectCreationParams(type), 
                        templateCreature(templateCreature), name(name)  
    {
       
    }
    virtual ~CPawnCreationParams()
    {
        
    }
    CCreatureCreationParams templateCreature;
    std::string name;
};

class CObject;
class CCreature;
class CMovableObject;
class CPawn : public IUpdatable, public IJSONSerializable, public IDBSerializable
{
friend class CSpawner;
public:
    CPawn(const int dbId);
    virtual ~CPawn();
    
    const std::string& getKey() const
    {
        return key;
    }
    bool getIsOnMap() const;
    void spawnOnMap(const CCellCoords& cell, CMap& map);
    void removeFromMap();
    
    virtual const json toJSON() const;
protected:
    CPawn(const CObjectCreationParams& param);
    
    virtual void loadFromDB(const unsigned int dbId);
    virtual void saveToDB() const;
    void initCreature(const CPawnCreationParams& creationParams);
    
    unsigned int dbId;
    CMovableObject* mapObject;
    CCreature* creature;
    std::string name;
    std::string key;
    
    CObjectsPool<unsigned int, CObject> objects;
};