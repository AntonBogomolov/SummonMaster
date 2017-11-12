#pragma once 

#include "IUpdatable.h"
#include "src/Objects/CObject.h"
#include "CCellCoords.h"
#include "CMapObjectPosAndSizeDescriptor.h"

#include "src/IJSONSerializable.h"

enum class ENMapObjectBlockMode {notBlock = 0, blockOneTile, blockAllTiles};

class CMapObjectCreationParam
{
public:
    CMapObjectCreationParam(const CCellCoords& cellCoords, const CMapObjectPosAndSizeDescriptor& position, 
                            const ENMapObjectBlockMode blockMode = ENMapObjectBlockMode::notBlock,  const unsigned int layerId = 0) : 
                            cellCoords(cellCoords), position(position), blockMode(blockMode), layerId(layerId)
    {
        
    }
    ~CMapObjectCreationParam()
    {
        
    }    
    CCellCoords cellCoords;
    CMapObjectPosAndSizeDescriptor position;
    ENMapObjectBlockMode blockMode;
    unsigned int layerId;
protected:
    
};

class CMapObject : public IEventHandler, public IUpdatable, public IJSONSerializable
{
public:
    friend class CSpawner;

    CMapObject(CMapObject& mapObj)
    {
        this->position   = mapObj.getObjectPositionInCellDescriptor();
        this->cellCoords = mapObj.getCellCoords();
        this->isInstanceObject  = mapObj.getIsInstanceObject();
        this->blockMode         = mapObj.getBlockMode();
        this->layerId           = mapObj.getLayerId();
        this->instanceId        = CUtils::getInstance()->getRandomNumber();
        
        if(this->isInstanceObject) this->object = mapObj.getObjectForModify();
        else this->object = mapObj.ejectObjectForModify();
    }
   
    virtual ~CMapObject()
    {
        if(!isInstanceObject) delete object;
    }
    
    const CCellCoords getCellCoords() const
    {
        return cellCoords;
    }
    CCellCoords getCellCoordsForModify()
    {
        return cellCoords;
    }
    ENMapObjectBlockMode getBlockMode() const
    {
        return blockMode;
    }
    const CMapObjectPosAndSizeDescriptor getObjectPositionInCellDescriptor() const
    {
        return position;
    }
    CMapObjectPosAndSizeDescriptor getObjectPositionInCellDescriptorForModify()
    {
        return position;
    }
    const CObject* getObject() const
    {
        return object;
    }
    CObject* getObjectForModify()
    {
        return object;
    }
    CObject* ejectObjectForModify()
    {
        CObject* obj = object;
        object = nullptr;
        return obj;
    }
    bool getIsInstanceObject() const
    {
        return isInstanceObject;
    }
    ENObjectsType getType() const
    {
        if(object == nullptr) return ENObjectsType::NOTSET;
        return object->getObjectType();
    }
    unsigned int getObjectId() const
    {
        if(object == nullptr) return 0;
        return object->getObjectId();
    }
    unsigned int getInstanceId() const
    {
        return instanceId;
    }
    unsigned int getLayerId() const
    {
        return layerId;
    }
    bool isValid() const
    {
        bool result = true;
        if(object == nullptr) return false;
        if(object->getIsValid()) return false;
        
        return result;
    }
    void getBlockedCells(std::vector<CCellCoords>& cells) const
    {
        if(blockMode == ENMapObjectBlockMode::notBlock) return;
        if(blockMode == ENMapObjectBlockMode::blockOneTile) 
        {
            cells.push_back(cellCoords);
            return;
        }
        
        int p1x;
        int p1y;
        int p2x;
        int p2y;
        
        p1x = (int)position.xCenter - (int)position.width / 2;
        p1y = (int)position.yCenter - (int)position.height / 2;
        
        p2x = (int)position.xCenter + (int)position.width / 2;
        p2y = (int)position.yCenter + (int)position.height / 2;
        
        CUtils::getInstance()->rotatePointRelative(p1x, p1y, position.rotation, position.xRotCenter, position.yRotCenter);
        CUtils::getInstance()->rotatePointRelative(p2x, p2y, position.rotation, position.xRotCenter, position.yRotCenter);
              
        int leftPoint = p1x;
        int upPoint = p2y;
        int rightPoint = p2x;
        int downPoint = p1y;
        
        if(leftPoint > p2x)  leftPoint  = p2x;
        if(downPoint > p2y)  downPoint  = p2y;
        if(rightPoint < p1x) rightPoint = p1x;
        if(upPoint < p1y)    upPoint    = p1y;
        
        int xCellStart = cellCoords.xCell;
        if(leftPoint < 0) xCellStart -= (1 + leftPoint / CMetrics::cellWidth);
        int xCellEnd = cellCoords.xCell;
        if(rightPoint > CMetrics::cellWidth) xCellEnd += 1 + (rightPoint - CMetrics::cellWidth) / CMetrics::cellWidth;
        
        int yCellStart = cellCoords.yCell;
        if(downPoint < 0) yCellStart -= (1 + downPoint / CMetrics::cellHeight);
        int yCellEnd = cellCoords.yCell;
        if(upPoint > CMetrics::cellHeight) yCellEnd += 1 + (upPoint - CMetrics::cellHeight) / CMetrics::cellHeight;
        
        for(int x = xCellStart; x <= xCellEnd; x++ )
        {
            for(int y = yCellStart; y <= yCellEnd; y++ )
            {
                cells.push_back(CCellCoords(x,y));
            }
        }
    }
    
    virtual const json toJSON() const
    {
        return json{
            {"xCell", cellCoords.xCell},
            {"yCell", cellCoords.yCell},
            {"position", position.toJSON()},
            {"object", object->toJSON()},
            {"isInstanceObject", isInstanceObject},
            {"blockMode", static_cast<int>(blockMode)},
            {"layerId", layerId},
            {"instanceId", instanceId}
        };
    }
protected:
    CMapObject(const CMapObjectCreationParam& params, CObject* object, const bool isInstance = true) : 
                    cellCoords(params.cellCoords), position(params.position), object(object), 
                    isInstanceObject(isInstance), blockMode(params.blockMode), layerId(params.layerId)
    {
        instanceId = CUtils::getInstance()->getRandomNumber();
    }

    CCellCoords cellCoords;
    CMapObjectPosAndSizeDescriptor position;
    CObject* object;
    bool isInstanceObject;
    ENMapObjectBlockMode blockMode;
    unsigned int layerId;
    unsigned int instanceId;
};

