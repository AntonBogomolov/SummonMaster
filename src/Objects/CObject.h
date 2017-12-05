#pragma once

#include "src/utils.h"
#include "CTags.h"
#include "src/CEventDispatcher.h"
#include "src/IJSONSerializable.h"

enum class ENObjectsType { NOTSET = 0, EFFECT, CREATURE, PLAYER, PAWN, SUMMON, MAP, INSTANCE };

class CObjectCreationParams
{
public:
    CObjectCreationParams(unsigned int objectId, const ENObjectsType type, const CTags& tags)
    {
        this->objectId = objectId;
        this->type = type;
        this->tags = tags;
    }
    CObjectCreationParams(const ENObjectsType type, const CTags& tags)
    {
        this->objectId = 0;
        this->type = type;
        this->tags = tags;
    }
    CObjectCreationParams(const ENObjectsType type)
    {
        this->objectId = 0;
        this->type = type;
        this->tags = CTags();
    }
    virtual ~CObjectCreationParams()
    {
        
    }
    
    unsigned int objectId;
    ENObjectsType type;
    CTags tags;
protected:    
};

class CObject : public IEventHandler, public IJSONSerializable
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
    CTags& getTagsForModify()
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
    void setObjectType(const ENObjectsType newType) 
    {
        objectType = newType;
    }
    bool isFilterFit(const CTagFilter& filter) const
    {
        const std::vector<int>& filterTags = filter.tags.getContainer();
        if(filter.filterMode == ENTagFilterMode::Or)
        {
            for(auto it = filterTags.begin(); it != filterTags.end(); ++it)
            {
                int currTagId = (*it);
                if(tags.isHasTag(currTagId)) return true;
            }
        }
        if(filter.filterMode == ENTagFilterMode::And)
        {
            for(auto it = filterTags.begin(); it != filterTags.end(); ++it)
            {
                int currTagId = (*it);
                if(!tags.isHasTag(currTagId)) return false;
            }
            return true;
        }
        if(filter.filterMode == ENTagFilterMode::Not)
        {
            for(auto it = filterTags.begin(); it != filterTags.end(); ++it)
            {
                int currTagId = (*it);
                if(tags.isHasTag(currTagId)) return false;
            }
            return true;
        }
        return false;
    }
    
    virtual const json toJSON() const
    {
        return json{
            {"objectId", objectId},
            {"objectType", static_cast<int>(objectType)},
            {"tags", tags.toJSON()}
        };
    }
protected:
    CObject(const CObjectCreationParams& params)
    {
        if(params.objectId == 0) this->objectId = CUtils::getInstance()->getRandomNumber();
        else this->objectId = params.objectId;
        
        this->objectType = params.type;
        this->tags = params.tags;
        this->isValid = true;
    } 
    
    unsigned int objectId;
    ENObjectsType objectType;
    CTags tags;
    bool isValid;
};
