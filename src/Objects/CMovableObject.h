#pragma once 

#include "src/Map/CMapObject.h"
#include "src/Map/CPathFinder.h"
#include "src/Map/CMap.h"
#include "src/Objects/IMovable.h"

class CMovableObjectCreationParam : public CMapObjectCreationParam
{
public:
    CMovableObjectCreationParam(const CCellCoords& cellCoords, const CMapObjectPosAndSizeDescriptor& position, 
                            const CCellCoords& pathTarget,
                            const ENMapObjectBlockMode blockMode = ENMapObjectBlockMode::notBlock,  
                            const unsigned int layerId = 0) 
                                : CMapObjectCreationParam(cellCoords, position, blockMode, layerId),
                                pathTarget(pathTarget)
                           
    {
        
    }
    ~CMovableObjectCreationParam()
    {
        
    }    

    const CCellCoords& getPathTarget() const
    {
        return pathTarget;
    }
protected:
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
        movableInterface = dynamic_cast<IMovable*>(object);
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
    unsigned int getMoveCost(const CTileData& tileData) const
    {
        if(movableInterface == nullptr) return std::numeric_limits<unsigned int>::max();
        return movableInterface->getMoveCost(tileData);
    }
    float setPathTarget(const CCellCoords& pathEndPoint)
    {
        float pathTime = 0.0f;
        if(movableInterface == nullptr) return pathTime;
        
        if(pathEndPoint != CCellCoords(0,0))
        {
            const CPathFinder& pathFinder = ownerMap->getPathFinder();
            this->path = pathFinder.findPath(cellCoords, pathEndPoint, this);
            this->pathEndPoint = pathEndPoint;
            
            pathTime = this->path.getPathCost() / movableInterface->getMoveSpeed();
        }
        return pathTime;
    }
    
    virtual const json toJSON() const
    {
        json result = CMapObject::toJSON();
        result["pathEndPointCol"] = pathEndPoint.col;
        result["pathEndPointRow"] = pathEndPoint.row;
        result["path"] = path.toJSON();
        if(movableInterface != nullptr) result["moveSpeed"] = movableInterface->getMoveSpeed();
        return result;
    }

    virtual void update(const float dt);
    
protected:
    CMovableObject(const CMapObjectCreationParam& params, CMap* map, CObject* object, const bool isInstance = true) 
                    : CMapObject(params, map, object, isInstance),
                    pathEndPoint(getCellCoords()), path()
    {
        const CMovableObjectCreationParam& movableCreationParams = static_cast<const CMovableObjectCreationParam&>(params);
        pathEndPoint = movableCreationParams.getPathTarget();
        
        movableInterface = dynamic_cast<IMovable*>(object);
        if(movableInterface != nullptr && pathEndPoint != CCellCoords(0,0))
        {
            object->getTagsForModify().addTag(CTagMap::getInstance()->getTagId("MOVABLE"));
            const CPathFinder& pathFinder = ownerMap->getPathFinder();
            path = pathFinder.findPath(cellCoords, pathEndPoint, this);
        }
    }

    CCellCoords pathEndPoint;
    CPathOnMap path;
    IMovable* movableInterface;
};