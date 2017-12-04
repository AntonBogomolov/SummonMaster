#include "src/Creatures/CPlayer.h"

#include "src/Creatures/CCreature.h"
#include "src/Creatures/CCharacteristics.h"
#include "src/Objects/CMovableObject.h"
#include "src/Objects/CSpawner.h"
#include "src/World/CWorld.h"

CPlayer::CPlayer(const int dbPlayerId)
{
    dbId = 0;
    name = "";
    creature = nullptr;
    mapObject = nullptr;
    
    loadFromDB(dbPlayerId);
}
CPlayer::CPlayer(const CObjectCreationParams& param)
{
    const CPlayerCreationParams& playerParams = static_cast<const CPlayerCreationParams&>(param);
    
    this->dbId = 0;
    this->mapObject = nullptr;
    this->name = name;
    
    initCreature(playerParams);
}
CPlayer::~CPlayer()
{
    if(mapObject) 
    {
        const CCellCoords& cell = mapObject->getCellCoords();
        mapObject->getOwnerMap()->getObjectsOnMapCollectionForModify().removeMapObject(cell, mapObject);
    }
}

void CPlayer::initCreature(const CPlayerCreationParams& creationParams)
{
    CWorld* world = CWorld::getInstance();
    CSpawner& spawner = world->getSpawnerForModify();
    
    CResistances resists;
    CEffects effects;
    CCharacteristics characteristics;
    
    CCreatureCreationParams creatureParams(resists, characteristics, effects);
    creature = dynamic_cast<CCreature*>(spawner.createObject<CCreature>(objects, creatureParams));
    creature->setObjectType(ENObjectsType::PLAYER);
}

void CPlayer::spawnOnMap(const CCellCoords& cell, CMap& map)
{
    if(creature == nullptr) return;
    if(mapObject) removeFromMap();
    
    CWorld* world = CWorld::getInstance();
    CSpawner& spawner = world->getSpawnerForModify();
    
    CMapObjectPosAndSizeDescriptor pos;
    CMovableObjectCreationParam movableObjParams(cell, pos, cell);
    mapObject = dynamic_cast<CMovableObject*>(spawner.spawnInstanceMapObject<CMovableObject>(map, movableObjParams, creature));    
}
void CPlayer::removeFromMap()
{
    if(mapObject) 
    {
        const CCellCoords& cell = mapObject->getCellCoords();
        mapObject->getOwnerMap()->getObjectsOnMapCollectionForModify().removeMapObject(cell, mapObject);
        mapObject = nullptr;
    }
}
    
void CPlayer::loadFromDB(const unsigned int dbId)
{
    CPlayerCreationParams creationsParams(ENPlayerPreset::DEFAULT, "");
    initCreature(creationsParams);
}
void CPlayer::saveToDB() const
{
    
}

void CPlayer::update(const float dt)
{
    if(isNeedToUpdate)
    {
        if(creature && !getIsOnMap()) creature->update(dt);
    }
}

bool CPlayer::getIsOnMap() const
{
    if(mapObject == nullptr) return false;
    if(!mapObject->getOwnerMap()) return false;
    return true;
}

const json CPlayer::toJSON() const
{
    json result = json::object();
    result["movableObject"] = mapObject->toJSON();
    result["creature"]      = creature->toJSON();
    result["name"]          = name;
    return result;
}