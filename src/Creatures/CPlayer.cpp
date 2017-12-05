#include "src/Creatures/CPlayer.h"

#include "src/Creatures/CCreature.h"
#include "src/Creatures/CCharacteristics.h"
#include "src/Objects/CMovableObject.h"
#include "src/Objects/CSpawner.h"
#include "src/World/CWorld.h"

CPlayer::CPlayer(const int dbPlayerId) : CPawn(dbPlayerId)
{
    loadFromDB(dbPlayerId);
}
CPlayer::CPlayer(const CObjectCreationParams& param) : CPawn(param)
{
    const CPlayerCreationParams& playerParams = static_cast<const CPlayerCreationParams&>(param);
    if(creature) creature->setObjectType(ENObjectsType::PLAYER);
}
CPlayer::~CPlayer()
{
   
}

void CPlayer::loadFromDB(const unsigned int dbId)
{
    CPawn::loadFromDB(dbId);
    if(creature) creature->setObjectType(ENObjectsType::PLAYER);
}
void CPlayer::saveToDB() const
{
    CPawn::saveToDB();
}

void CPlayer::update(const float dt)
{
    if(isNeedToUpdate)
    {
        if(creature && !getIsOnMap()) creature->update(dt);
    }
}

const json CPlayer::toJSON() const
{
    json result = CPawn::toJSON();
   
    return result;
}

CCreatureCreationParams CPlayer::getCreationParamsByPreset(const ENPlayerPreset preset)
{
    CResistances resists;
    CCharacteristics characteristics;
    CEffects effects;
    
    CCreatureCreationParams params(resists, characteristics, effects);
    return params;
}