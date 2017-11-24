#pragma once 

#include "src/Map/CMapObject.h"
#include "src/Map/CPathFinder.h"

class CMovableObjectCreationParam : public CMapObjectCreationParam
{
public:
    CMovableObjectCreationParam(const CCellCoords& cellCoords, const CMapObjectPosAndSizeDescriptor& position, 
                            const ENMapObjectBlockMode blockMode = ENMapObjectBlockMode::notBlock,  
                            const unsigned int layerId = 0) : CMapObjectCreationParam(cellCoords, position, blockMode, layerId)
                           
    {
        
    }
    ~CMovableObjectCreationParam()
    {
        
    }    

protected:
    
};

class CTileData;
class CMovableObject : public CMapObject
{
public:
    friend class CSpawner;
    CMovableObject(CMovableObject& obj) : CMapObject(obj)
    {
        
    }
    virtual ~CMovableObject()
    {
        
    }
    
    const CCellCoords& getPathEndCell() const
    {
        return pathEndPoint;
    }
    const CCellCoords& getCurrCell() const 
    {
        return getCellCoords();
    }
    const CPathOnMap& getPath() const
    {
        return path;
    }
    
    virtual const json toJSON() const
    {
        json result = CMapObject::toJSON();
        //result["isActive"]    = isActive;
        return result;
    }
    
    virtual unsigned int getMoveCost(const CTileData& tile) const;
    
protected:
    CMovableObject(const CMovableObjectCreationParam& params, CObject* object, const bool isInstance = true) 
                    : CMapObject(params, object, isInstance)
    {
        
    }
    
    CCellCoords pathEndPoint;
    CPathOnMap path;
};