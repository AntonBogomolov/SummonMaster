#pragma once

#include "src/Creatures/CPawn.h"

enum class ENPlayerPreset{CUSTOM = 0, DEFAULT};

class CPlayerCreationParams : public CPawnCreationParams
{
public:
    CPlayerCreationParams(const CCreatureCreationParams& templateCreature, const std::string& name) 
                        : CPawnCreationParams(ENObjectsType::PLAYER, templateCreature, name)
                      
                            
    {
    }
    virtual ~CPlayerCreationParams()
    {
    }
};

class CPlayer : public CPawn
{
friend class CSpawner;
public:
    CPlayer(const int dbPlayerId);
    virtual ~CPlayer();

    virtual void update(const float dt);
    virtual const json toJSON() const;
    
    static CCreatureCreationParams getCreationParamsByPreset(const ENPlayerPreset preset);
protected:
    CPlayer(const CObjectCreationParams& param);
    
    virtual void loadFromDB(const unsigned int dbId);
    virtual void saveToDB() const;
};