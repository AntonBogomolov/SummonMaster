#include "CMovableObject.h"
#include "src/Map/CTileData.h"


void CMovableObject::update(const float dt)
{
    CMapObject::update(dt);
    
    if(isNeedToUpdate && !path.getIsEmpty() && movableInterface != nullptr)
    {
        float moveSpeedKoeff = movableInterface->getMoveCost(ownerMap->getTileAtFast(cellCoords.row, cellCoords.col)) / CMetrics::baseMoveCost;
        float dl = (dt * movableInterface->getMoveSpeed() * CMetrics::cellWidth) / moveSpeedKoeff;
        
        if(dl < CMetrics::cellWidth)
        {
            const CPathNode topNode = path.path.front();
            ENDirection dir = cellCoords.getDirection(CCellCoords(topNode.col, topNode.row));
            bool isNeedToChangeCell = false;
            CCellCoords oldCell = cellCoords;
            
            if(dir == ENDirection::Up)
            {
                if(dl <= position.yCenter) position.yCenter -= dl;
                else
                if(dl >  position.yCenter && cellCoords.row > 0)
                {
                    isNeedToChangeCell = true;
                    cellCoords.row--;
                    position.yCenter = CMetrics::cellHeight - (dl - position.yCenter) - 1;
                }
                else position.yCenter = 0;
            }else 
            if(dir == ENDirection::Down)
            {
                position.yCenter += dl;
                unsigned int div = position.yCenter / CMetrics::cellHeight;
                unsigned int mod = position.yCenter % CMetrics::cellHeight;
                if(div > 0 && cellCoords.row < ownerMap->getHeight())
                {
                    isNeedToChangeCell = true;
                    cellCoords.row++;
                    position.yCenter = mod;
                }
                else position.yCenter = CMetrics::cellHeight - 1;
            }else 
            if(dir == ENDirection::Left)
            {
                if(dl <= position.xCenter) position.xCenter -= dl;
                else
                if(dl >  position.xCenter && cellCoords.col > 0)
                {
                    isNeedToChangeCell = true;
                    cellCoords.col--;
                    position.xCenter = CMetrics::cellWidth - (dl - position.xCenter) - 1;
                }
                else position.xCenter = 0;
            }else 
            if(dir == ENDirection::Right)
            {
                position.xCenter += dl;
                unsigned int div = position.xCenter / CMetrics::cellWidth;
                unsigned int mod = position.xCenter % CMetrics::cellWidth;
                if(div > 0 && cellCoords.col < ownerMap->getWidth())
                {
                    isNeedToChangeCell = true;
                    cellCoords.col++;
                    position.xCenter = mod;
                }
                else position.xCenter = CMetrics::cellWidth - 1;
            }
                
            if(isNeedToChangeCell)
            {
                CChangeObjectCellEventParam* param = new CChangeObjectCellEventParam(this, oldCell, cellCoords);
                ownerMap->receiveMessage(*this, param);
                delete param;
            }
            
        }
    }
}