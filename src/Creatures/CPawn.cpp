#include "src/Creatures/CPawn.h"

#include "src/Creatures/CCreature.h"
#include "src/Creatures/CCharacteristics.h"
#include "src/Objects/CMovableObject.h"
#include "src/Objects/CSpawner.h"
#include "src/World/CWorld.h"

#include <novemberlib/utils/CLog.h>

CPawn::CPawn(const int dbId)
{
    this->dbId = dbId;
    name = "";
    creature = nullptr;
    mapObject = nullptr;
    key = "";
}
CPawn::CPawn(const CObjectCreationParams& param)
{
    const CPawnCreationParams& params = static_cast<const CPawnCreationParams&>(param);
    
    this->dbId = 0;
    this->mapObject = nullptr;
    this->name = params.name;
    this->key = CUtils::getInstance()->genRndHashKey();
    
    initCreature(params);
}
CPawn::~CPawn()
{
    if(mapObject) 
    {
        const CCellCoords& cell = mapObject->getCellCoords();
        mapObject->getOwnerMap()->getObjectsOnMapCollectionForModify().removeMapObject(cell, mapObject);
    }
}

void CPawn::initCreature(const CPawnCreationParams& creationParams)
{
    CWorld* world = CWorld::getInstance();
    CSpawner& spawner = world->getSpawnerForModify();
    
    CResistances resists = creationParams.templateCreature.resistances;
    CEffects effects = creationParams.templateCreature.effects;
    CCharacteristics characteristics = creationParams.templateCreature.characteristics;
    
    CCreatureCreationParams creatureParams(resists, characteristics, effects);
    creature = dynamic_cast<CCreature*>(spawner.createObject<CCreature>(objects, creatureParams));
}

void CPawn::spawnOnMap(const CCellCoords& cell, CMap& map)
{
    if(creature == nullptr) return;
    if(mapObject) removeFromMap();
    
    CWorld* world = CWorld::getInstance();
    CSpawner& spawner = world->getSpawnerForModify();
    
    CMapObjectPosAndSizeDescriptor pos;
    CMovableObjectCreationParam movableObjParams(cell, pos, cell);
    mapObject = dynamic_cast<CMovableObject*>(spawner.spawnInstanceMapObject<CMovableObject>(map, movableObjParams, creature));    
}
void CPawn::removeFromMap()
{
    if(mapObject) 
    {
        const CCellCoords& cell = mapObject->getCellCoords();
        mapObject->getOwnerMap()->getObjectsOnMapCollectionForModify().removeMapObject(cell, mapObject);
        mapObject = nullptr;
    }
}
    
void CPawn::loadFromDB(const unsigned int dbId)
{
    CResistances resists;
    CEffects effects;
    CCharacteristics characteristics;
    
    CCreatureCreationParams defaultParams(resists, characteristics, effects);
    CPawnCreationParams creationsParams(ENObjectsType::PAWN, defaultParams, "");
    
    initCreature(creationsParams);
}
void CPawn::saveToDB() const
{
    
}

bool CPawn::getIsOnMap() const
{
    if(mapObject == nullptr) return false;
    if(!mapObject->getOwnerMap()) return false;
    return true;
}

const json CPawn::toJSON() const
{
    json result = json::object();
    if(getIsOnMap()) result["movableObject"] = mapObject->toJSON();
    result["creature"]      = creature->toJSON();
    result["name"]          = name;
    result["key"]           = key;
    return result;
}