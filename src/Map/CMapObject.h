#pragma once 

#include "src/Objects/CObject.h"
#include "CCellCoords.h"
#include "CMapObjectPosAndSizeDescriptor.h"

class CMapObjectCreationParam
{
public:
    CMapObjectCreationParam(const CCellCoords& cellCoords, const CMapObjectPosAndSizeDescriptor& position, const bool isBlocking) : 
                            cellCoords(cellCoords), position(position), isBlocking(isBlocking)
    {
        
    }
    ~CMapObjectCreationParam()
    {
        
    }    
    CCellCoords cellCoords;
    CMapObjectPosAndSizeDescriptor position;
    bool isBlocking;
protected:
    
};

class CMapObject : public IEventHandler, IUpdatable
{
public:
    friend class CSpawner;

    CMapObject(CMapObject& mapObj)
    {
        this->position   = mapObj.getObjectPositionInCellDescriptor();
        this->cellCoords = mapObj.getCellCoords();
        this->isInstanceObject  = mapObj.getIsInstanceObject();
        this->isBlocking        = mapObj.getIsBlocking();
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
    bool getIsBlocking() const
    {
        return isBlocking;
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
    bool isValid() const
    {
        bool result = true;
        if(object == nullptr) return false;
        if(object->getIsValid()) return false;
        
        return result;
    }
    void getBlockedCells(std::vector<CCellCoords>& cells) const
    {
        if(!isBlocking) return;
        
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
    
    virtual void update(const float dt)
    {
        
    }
protected:
    CMapObject(const CMapObjectCreationParam& params, CObject* object, const bool isInstance = true) : 
                    cellCoords(params.cellCoords), position(params.position), object(object), 
                    isInstanceObject(isInstance), isBlocking(params.isBlocking)
    {
        instanceId = CUtils::getInstance()->getRandomNumber();
    }

    CCellCoords cellCoords;
    CMapObjectPosAndSizeDescriptor position;
    CObject* object;
    bool isInstanceObject;
    bool isBlocking;
    unsigned int instanceId;
};

