#pragma once 

#include "src/Map/CMap.h"

class CInstanceCreationParams : public CObjectCreationParams
{
public:
    CInstanceCreationParams(const CMapCreationParams& mapCreationParams, const float lifeTime = 9000.0f,
                            const bool isLifeTimeNeverEnd = false) : CObjectCreationParams(ENObjectsType::INSTANCE),
                            mapCreationParams(mapCreationParams), lifeTime(lifeTime), isLifeTimeNeverEnd(isLifeTimeNeverEnd)
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
public:
    CMapCreationParams mapCreationParams;
    float lifeTime;
    bool isLifeTimeNeverEnd;
};

class CInstance : public CObject, public IUpdatable
{
public:
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
    bool getIsLifeTimeNeverEnd() const
    {
        return isLifeTimeNeverEnd;
    }
    
    virtual void update(const float dt);
protected:
    CInstance(const CObjectCreationParams& param);
    
    CMap* map;
    float lifeTime;
    bool isLifeTimeNeverEnd;
};