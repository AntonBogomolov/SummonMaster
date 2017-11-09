#pragma once

#include "IUpdatable.h"
#include "src/Objects/CObject.h"
#include "src/Objects/CObjectContainer.h"

#include "CCharacteristics.h"
#include "CEffects.h"
#include "CResistances.h"
#include "src/Objects/CTags.h"

#include <string>
#include <vector>

class CCreatureCreationParams : public CObjectCreationParams
{
public:
    CCreatureCreationParams(const CResistances& resistances, const CCharacteristics& characteristics, 
                            const CEffects& effects) : CObjectCreationParams(ENObjectsType::CREATURE),
                            resistances(resistances), characteristics(characteristics), effects(effects)
    {
       
    }
    virtual ~CCreatureCreationParams()
    {
        
    }
    
    CResistances resistances;
    CCharacteristics characteristics;
    CEffects effects;
protected:    
};

class CCreature : public CObject, public IUpdatable
{
public:
    CCreature(const CCreature& creature);
    virtual ~CCreature();
    
    const CResistances& getResistances() const
    {
        return resistances;
    }
    const CCharacteristics& getCharacteristics() const
    {
        return characteristics;
    }
    CCharacteristics& getCharacteristicsForModify()
    {
        return characteristics;
    }
    const CEffects& getEffects() const
    {
        return effects;
    }
    virtual void update(const float dt);  
    
    virtual const json toJSON() const
    {
        return json{
            CObject::toJSON(),
            {"resistances", resistances.toJSON()},
            {"characteristics", characteristics.toJSON()},
            {"effects", effects.toJSON()}
        };
    }
protected:
    CCreature(const CObjectCreationParams& param); 

    CResistances resistances;
    CCharacteristics characteristics;
    CEffects effects;
};