#pragma once 

#include "IUpdatable.h"
#include "CInstance.h"
#include <map>

#include "CSyncHelper.h"


class CInstanceManager : public IUpdatable
{
public:
    CInstanceManager()
    {
        setIsNeedToUpdate(true);
    }
    ~CInstanceManager()
    {
        for(auto it = instances.begin(); it != instances.end();)
        {
            delete it->second;
            instances.erase(it);
        }
    }
    
    bool getIsInstanceExist(const unsigned int id) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            return true;
        }
        return false;
    }
    const CInstance* getInstance(const unsigned int id) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            return it->second;
        }
        return nullptr;
    }
    CInstance* getInstanceForModify(const unsigned int id)
    {
        std::shared_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            return it->second;
        }
        return nullptr;
    }
    void deleteInstance(const unsigned int id)
    {
        std::unique_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            delete it->second;
            instances.erase(it);
        }
    }
    
    void addInstance(CInstance* newInstance)
    {
        if(!newInstance) return;
        bool isExist = getIsInstanceExist(newInstance->getObjectId());
        if(isExist)
        {
            delete newInstance;
            return;
        }
        
        std::unique_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        instances[newInstance->getObjectId()] = newInstance;
    }
    
    void clearGarbage() 
    {
        std::unique_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        
        for(auto it = instances.begin(); it != instances.end();)
        {
            CInstance* currInst = it->second;
            if(!currInst->getIsLifeTimeNeverEnd() && currInst->getLifeTime() < 0.0f)
            {
                delete it->second;
                instances.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    
    virtual void update(const float dt)
    {
        std::shared_lock<std::shared_timed_mutex> lock(*CSyncHelper::getInstance()->getInstanceMutex());
        
        for(auto it = instances.begin(); it != instances.end();)
        {
            CInstance* currInst = it->second;
            if(currInst->getIsValid() && currInst->getIsNeedToUpdate())
            {
                currInst->update(dt);
            }
        }
    }
    
    CInstanceManager(const CInstanceManager& inst) = delete;
protected:
    std::map<unsigned int, CInstance*> instances;
};