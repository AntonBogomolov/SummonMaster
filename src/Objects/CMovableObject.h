#pragma once 

#include "src/Map/CMapObject.h"

class CMovableObjectCreationParam
{
public:
    CMovableObjectCreationParam(const CCellCoords& cellCoords, const CMapObjectPosAndSizeDescriptor& position, 
                            const ENMapObjectBlockMode blockMode = ENMapObjectBlockMode::notBlock,  
                            const unsigned int layerId = 0) : CMapObjectCreationParam(cellCoords, position, blockMode, layerId),
                           
    {
        
    }
    ~CMovableObjectCreationParam()
    {
        
    }    

protected:
    
};

class CMovableObject : public CMapObject
{
public:
    friend class CSpawner;
    CMovableObject(const CMovableObject& obj) : CMapObject(obj)
    {
        
    }
    ~CMovableObject()
    {
        
    }
    
protected:
    CMovableObject(const CMovableObjectCreationParam& params, CObject* object, const bool isInstance = true) 
                    : CMapObject(params, object, isInstance)
    {
        
    }
};