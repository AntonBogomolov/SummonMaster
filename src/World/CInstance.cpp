#include "CInstance.h"

CInstance::CInstance(const CObjectCreationParams& param) : CObject(param), 
{
    setIsNeedToUpdate(true);
    const CInstanceCreationParams& instanceParams
}

CInstance::~CInstance()
{
    delete map;
}

void CInstance::update(const float dt)
{
    lifeTime -= dt;
    if(lifeTime < 0.0f)  setIsNeedToUpdate(false);        
}