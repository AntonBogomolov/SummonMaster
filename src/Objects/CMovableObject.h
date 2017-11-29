#pragma once 

#include "src/Map/CMapObject.h"
#include "src/Map/CPathFinder.h"
#include "src/Map/CMap.h"

class CMovableObjectCreationParam : public CMapObjectCreationParam
{
public:
    CMovableObjectCreationParam(const CCellCoords& cellCoords, const CMapObjectPosAndSizeDescriptor& position, 
                            const float moveSpeed, const CCellCoords& pathTarget,
                            const ENMapObjectBlockMode blockMode = ENMapObjectBlockMode::notBlock,  
                            const unsigned int layerId = 0) 
                                : CMapObjectCreationParam(cellCoords, position, blockMode, layerId),
                                moveSpeed(moveSpeed), pathTarget(pathTarget)
                           
    {
        
    }
    ~CMovableObjectCreationParam()
    {
        
    }    

    float getMoveSpeed() const
    {
        return moveSpeed;
    }
    const CCellCoords& getPathTarget() const
    {
        return pathTarget;
    }
protected:
    float moveSpeed;
    CCellCoords pathTarget;
};

class CTileData;
class CMovableObject : public CMapObject
{
public:
    friend class CSpawner;
    CMovableObject( CMovableObject& obj) : CMapObject(obj),
                    pathEndPoint(obj.getPathEndCell()), path(obj.getPath())
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
        return cellCoords;
    }
    const CPathOnMap& getPath() const
    {
        return path;
    }
    float setPathTarget(const CCellCoords& pathEndPoint)
    {
        float pathTime = 0.0f;
        if(pathEndPoint != CCellCoords(0,0))
        {
            const CPathFinder& pathFinder = ownerMap->getPathFinder();
            this->path = pathFinder.findPath(cellCoords, pathEndPoint, this);
            this->pathEndPoint = pathEndPoint;
            
            pathTime = this->path.getPathCost() / this->moveSpeed;
        }
        return pathTime;
    }
    
    virtual const json toJSON() const
    {
        json result = CMapObject::toJSON();
        result["pathEndPointCol"] = pathEndPoint.col;
        result["pathEndPointRow"] = pathEndPoint.row;
        result["path"] = path.toJSON();
        result["moveSpeed"]  = moveSpeed;
        return result;
    }
    
    virtual unsigned int getMoveCost(const CTileData& tile) const;
    virtual void update(const float dt);
    
protected:
    CMovableObject(const CMovableObjectCreationParam& params, CMap* map, CObject* object, const bool isInstance = true) 
                    : CMapObject(params, map, object, isInstance),
                    pathEndPoint(params.getPathTarget()), path(), moveSpeed(params.getMoveSpeed())
    {
        if(pathEndPoint != CCellCoords(0,0))
        {
            object->getTagsForModify().addTag(CTagMap::getInstance()->getTagId("MOVABLE"));
            const CPathFinder& pathFinder = ownerMap->getPathFinder();
            path = pathFinder.findPath(cellCoords, pathEndPoint, this);
        }
    }

    CCellCoords pathEndPoint;
    CPathOnMap path;
    float moveSpeed;
};