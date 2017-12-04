#pragma once

#include "src/IJSONSerializable.h"
#include "src/IDBSerializable.h"
#include "src/IUpdatable.h"
#include "src/Objects/CObjectsPool.h"
#include "src/Map/CMap.h"

#include <string>

enum class ENPlayerPreset{CUSTOM = 0, DEFAULT};

class CPlayerCreationParams : public CObjectCreationParams
{
public:
    CPlayerCreationParams(const ENPlayerPreset preset, const std::string& name) 
                        : CObjectCreationParams(ENObjectsType::PLAYER),
                        preset(preset), name(name)
                            
    {
       
    }
    virtual ~CPlayerCreationParams()
    {
        
    }
    
    ENPlayerPreset preset;
    std::string name;
};

class CObject;
class CCreature;
class CMovableObject;
class CPlayer : public IUpdatable, public IJSONSerializable, public IDBSerializable
{
friend class CSpawner;
public:
    CPlayer(const int dbPlayerId);
    virtual ~CPlayer();
    
    bool getIsOnMap() const;
    void spawnOnMap(const CCellCoords& cell, CMap& map);
    void removeFromMap();
    
    virtual void update(const float dt);
    virtual const json toJSON() const;
protected:
    CPlayer(const CObjectCreationParams& param);
    
    virtual void loadFromDB(const unsigned int dbId);
    virtual void saveToDB() const;
    void initCreature(const CPlayerCreationParams& creationParams);
    
    unsigned int dbId;
    CMovableObject* mapObject;
    CCreature* creature;
    std::string name;
    
    CObjectsPool<CObject> objects;
};