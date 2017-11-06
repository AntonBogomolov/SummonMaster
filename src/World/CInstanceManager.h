#pragma once 

#include "IUpdatable.h"
#include "CInstance.h"
#include <map>

#include <mutex>
#include <shared_mutex>

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
        std::shared_lock<std::shared_timed_mutex> lock(mtxInstance);
      
        auto it = instances.find(id);
        if(it != instances.end())
        {
            return true;
        }
        return false;
    }
    const CInstance* getInstance(const unsigned int id) const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mtxInstance);
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            return it->second;
        }
        return nullptr;
    }
    CInstance* getInstanceForModify(const unsigned int id)
    {
        std::shared_lock<std::shared_timed_mutex> lock(mtxInstance);
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            return it->second;
        }
        return nullptr;
    }
    void deleteInstance(const unsigned int id)
    {
        std::unique_lock<std::shared_timed_mutex> lock(mtxInstance);
        
        auto it = instances.find(id);
        if(it != instances.end())
        {
            delete it->second;
            instances.erase(it);
        }
    }
    
    unsigned int addInstance(CInstance* newInstance)
    {
        if(!newInstance) return 0;
        bool isExist = getIsInstanceExist(newInstance->getObjectId());
        if(isExist)
        {
            delete newInstance;
            return 0;
        }
        
        std::unique_lock<std::shared_timed_mutex> lock(mtxInstance);
        instances[newInstance->getObjectId()] = newInstance;
        return newInstance->getObjectId();
    }
    
    void clearGarbage() 
    {
        std::unique_lock<std::shared_timed_mutex> lock(mtxInstance);
        
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
        std::shared_lock<std::shared_timed_mutex> lock(mtxInstance);
        
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
    mutable std::shared_timed_mutex mtxInstance;
};