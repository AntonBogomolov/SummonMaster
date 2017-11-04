#pragma once 


#include "src/Objects/CObject.h"

class CInstanceCreationParams : public CObjectCreationParams
{
public:
    CInstanceCreationParams(const CMapCreationParams& mapCreationParams) : CObjectCreationParams(ENObjectsType::INSTANCE),
                            mapCreationParams(mapCreationParams)
    {
        
    }
    ~CInstanceCreationParams()
    {
        
    }
    const mapCreationParams& getMapCreationParams() const
    {
        return mapCreationParams;
    }
    long getLifeTime() const
    {
        return lifeTime;
    }
protected:
    CMapCreationParams mapCreationParams;
    long lifeTime;
    
};

class CMap;
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
    
    virtual void update(const float dt);
protected:
    CInstance(const CObjectCreationParams& param);
    
    CMap* map;
    long lifeTime;
};