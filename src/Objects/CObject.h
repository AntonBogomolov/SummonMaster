#pragma once

#include "utils.h"
#include "CTags.h"
#include "CEventDispatcher.h"

enum class ENObjectsType { NOTSET, EFFECT, CREATURE, MAP, INSTANCE };

class CObjectCreationParams
{
public:
    CObjectCreationParams(const ENObjectsType type, const CTags& tags)
    {
        this->type = type;
        this->tags = tags;
    }
    CObjectCreationParams(const ENObjectsType type)
    {
        this->type = type;
        this->tags = CTags();
    }
    virtual ~CObjectCreationParams()
    {
        
    }
    
    ENObjectsType type;
    CTags tags;
protected:    
};

class CObject : public IEventHandler
{
public:
    friend class CSpawner;
    
    CObject(const CObject& obj)
    {
        this->objectId   = obj.getObjectId();
        this->objectType = obj.getObjectType();
        this->tags = obj.getTags();
        this->isValid = obj.getIsValid();      
    }  
    virtual ~CObject(){};
    
    unsigned int getObjectId() const
    {
        return objectId;
    }
    ENObjectsType getObjectType() const
    {
        return objectType;
    }
    const CTags& getTags() const
    {
        return tags;
    }  
    bool getIsValid() const
    {
        return isValid;
    }
    void setIsValid(const bool isValid)
    {
        this->isValid = isValid;
    }
protected:
    CObject(const CObjectCreationParams& params)
    {
        this->objectId = CUtils::getInstance()->getRandomNumber();
        this->objectType = params.type;
        this->tags = params.tags;
        this->isValid = true;
    } 
    
    unsigned int objectId;
    ENObjectsType objectType;
    CTags tags;
    bool isValid;
};
