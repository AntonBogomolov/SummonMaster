#pragma once 

#include "src/Map/CMap.h"
#include <string>

class CInstanceCreationParams : public CObjectCreationParams
{
public:
    CInstanceCreationParams(const CMapCreationParams& mapCreationParams, const std::string& description = "",
                            const bool isLifeTimeNeverEnd = false, const float lifeTime = 9000.0f) : CObjectCreationParams(ENObjectsType::INSTANCE),
                            mapCreationParams(mapCreationParams), description(description), isLifeTimeNeverEnd(isLifeTimeNeverEnd), lifeTime(lifeTime)
    { 
        
    }
    ~CInstanceCreationParams()
    {
        
    }
    const CMapCreationParams& getMapCreationParams() const
    {
        return mapCreationParams;
    }
    float getLifeTime() const
    {
        return lifeTime;
    }
    const std::string getDescription() const
    {
        return description;
    }
public:
    CMapCreationParams mapCreationParams;
    std::string description;
    bool isLifeTimeNeverEnd;
    float lifeTime;
};

class CInstance : public CObject, public IUpdatable
{
public:
    friend class CSpawner;
    CInstance(const CInstance& inst) = delete;
    virtual ~CInstance();
    
    const CMap* getMap() const
    {
        return map;
    }
    CMap* getMapForModify() 
    {
        return map;
    }
    float getLifeTime() const
    {
        return lifeTime;
    }
    bool getIsLifeTimeEnd() const
    {
        return lifeTime < 0.0f;
    }
    bool getIsLifeTimeNeverEnd() const
    {
        return isLifeTimeNeverEnd;
    }
    const std::string& getDescription() const
    {
        return description;
    }
    
    virtual void update(const float dt);
protected:
    CInstance(const CObjectCreationParams& param);
    
    CMap* map;
    float lifeTime;
    bool isLifeTimeNeverEnd;
    std::string description;
};