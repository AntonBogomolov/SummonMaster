#pragma once

#include "src/Objects/CObject.h"
#include "src/Objects/CObjectContainer.h"

enum class ENEffect { NONE, IGNITE, FREEZE, SHOCK, POISONED, BLEEDING, PARALIZE };

class CEffectCreationParams : public CObjectCreationParams
{
public:
    CEffectCreationParams(bool isPermanent, float duration, float value, ENEffect effectType, int param) : 
                          CObjectCreationParams(ENObjectsType::EFFECT),
                          isActive(true), duration(duration), value(value), effectType(effectType), param(param)
    {
       
    }
    virtual ~CEffectCreationParams()
    {
        
    }
    
    bool isActive;
    bool isPermanent;
    float duration;
    float value;
    ENEffect effectType;
    int param;
protected:    
};

class CEffect : public CObject
{
public:
    
    CEffect(const CEffect& effect) : CObject(effect)
    {
        this->isActive          = effect.getIsActive();
        this->isPermanent       = effect.getIsPermanent();
        this->duration          = effect.getDuration();
        this->value             = effect.getValue();
        this->effectType        = effect.getEffectType();
        this->param             = effect.getParam();
    }
    virtual ~CEffect(){};
    
    bool getIsActive() const
    {
        return isActive;
    }
    void setIsActive(const bool isActive)
    {
        this->isActive = isActive;
    }
    bool getIsPermanent() const
    {
        return isPermanent;
    }
    float getDuration() const
    {
        return duration;
    }
    float getValue() const
    {
        return value;
    }
    ENEffect getEffectType() const
    {
        return effectType;
    }
    int getParam() const
    {
        return param;
    }
    
    void changeDuration(const float dt)
    {
        if(isActive) duration += dt;
    }
protected:
    CEffect(const CObjectCreationParams& param) : CObject(param)
    {
        const CEffectCreationParams& effectParams = static_cast<const CEffectCreationParams&>(param);
        this->isActive = effectParams.isActive;
        this->duration = effectParams.duration;
        this->value = effectParams.value;
        this->effectType = effectParams.effectType;
        this->param = effectParams.param;
        setIsValid(true);
    }

    bool isActive;
    bool isPermanent;
    float duration;
    float value;
    ENEffect effectType;
    int param;
};

class CEffects
{
public:
    CEffects()
    {
        
    }
    CEffects(const CEffects& effects) 
    {
        const CObjectContainer<CEffect>& effectsContainer = effects.getContainer();
        this->effects = effectsContainer;
    }
    ~CEffects()
    {
        
    }
    
    void update(const float dt)
    {
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end();)
        {
            CEffect& currEffect = (*it);
            currEffect.changeDuration(-1 * dt);
            if(currEffect.getDuration() < 0.0f) 
            {
                effectsVector.erase(it);               
            }
            else
            {
                ++it;
            }
        }       
    }
    void addEffect(const CEffect& effect)
    {
        if(getEffectById(effect.getObjectId()) == nullptr) effects.addObject(effect);
    }    
    const CObjectContainer<CEffect>& getContainer() const
    {
        return effects;
    }
    CObjectContainer<CEffect>& getContainerForModify()
    {
        return effects;
    }
    
    CEffect* getEffectByIdForModify(const unsigned int id)
    {
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            CEffect& currEffect = (*it);
            if(currEffect.getObjectId() == id) return &currEffect;
        }
        return nullptr;
    }
    const CEffect* getEffectById(const unsigned int id) const
    {
        const std::vector<CEffect>& effectsVector = effects.getContainer();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            const CEffect& currEffect = (*it);
            if(currEffect.getObjectId() == id) return &currEffect;
        }
        return nullptr;
    }
    
    const std::vector<CEffect*> getEffectsByType(const ENEffect type)
    {
        std::vector<CEffect*> resultEffects;
    
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            CEffect& currEffect = (*it);
            if(currEffect.getEffectType() == type) resultEffects.push_back(&currEffect);
        }
        return resultEffects;
    }    
    const std::vector<CEffect*> getPermanentEffects()
    {
        std::vector<CEffect*> resultEffects;
        
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            CEffect& currEffect = (*it);
            if(currEffect.getIsPermanent()) resultEffects.push_back(&currEffect);
        }
        return resultEffects;
    }    
    const std::vector<CEffect*> getActiveEffects()
    {
        std::vector<CEffect*> resultEffects;
        
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            CEffect& currEffect = (*it);
            if(currEffect.getIsActive()) resultEffects.push_back(&currEffect);
        }
        return resultEffects;
    } 
    const std::vector<CEffect*> getNotPermanentEffects()
    {
        std::vector<CEffect*> resultEffects;
        
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            CEffect& currEffect = (*it);
            if(!currEffect.getIsPermanent()) resultEffects.push_back(&currEffect);
        }
        return resultEffects;
    }    
    const std::vector<CEffect*> getNotActiveEffects()
    {
        std::vector<CEffect*> resultEffects;
        
        std::vector<CEffect>& effectsVector = effects.getContainerForModify();
        for(auto it = effectsVector.begin();it != effectsVector.end(); ++it)
        {
            CEffect& currEffect = (*it);
            if(!currEffect.getIsActive()) resultEffects.push_back(&currEffect);
        }
        return resultEffects;
    } 
protected:
    CObjectContainer<CEffect> effects;
};