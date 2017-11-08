#include "CInstance.h"

#include "src/Map/CMap.h"

CInstance::CInstance(const CObjectCreationParams& param) : CObject(param)
{
    setIsNeedToUpdate(true);
    const CInstanceCreationParams& instanceParams = static_cast<const CInstanceCreationParams&>(param);
    this->description = instanceParams.getDescription();
    this->lifeTime = instanceParams.getLifeTime();
    this->isLifeTimeNeverEnd = instanceParams.isLifeTimeNeverEnd;
    
    map = new CMap(instanceParams.getMapCreationParams());
}

CInstance::~CInstance()
{
    delete map;
}

void CInstance::update(const float dt)
{
    if(!isLifeTimeNeverEnd)
    {
        lifeTime -= dt;
        if(lifeTime < 0.0f)  setIsNeedToUpdate(false);
    }
}