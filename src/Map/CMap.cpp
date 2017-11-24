#include "CMap.h"

#include "CHeightMap.h"
#include "CMapObject.h"
#include "src/Objects/CMovableObject.h"

#include <iostream>
#include <iomanip>

CMap::CMap(const CMapCreationParams& param) : IEventHandler()
{
    tileMap = nullptr;
    blockMap = nullptr;
       
    this->width  = param.width;
    this->height = param.height;

    tileMap  = new CTileData*[height];
    blockMap = new bool*[height];
    for(unsigned int row = 0; row < height; row++)
    {
        tileMap[row]  = new CTileData[width];
        blockMap[row] = new bool[width];
    }
    
    pathFinder = new CPathFinderAStar(this);
    generateTileMap(param.generationParams);
    updateBlockMap(CCellCoords(0,0), CCellCoords(width-1, height-1));
}

void CMap::updateBlockMap(const CCellCoords& leftDownCorner, const CCellCoords& rightUpCorner)
{
    for(unsigned int x = leftDownCorner.col; x <= rightUpCorner.col; ++x)
    {
        for(unsigned int y = leftDownCorner.row; y <= rightUpCorner.row; ++y)
        {
            std::vector<CMapObject*>& objectsInCell = objectsOnMap.getAllMapObjectInCell(CCellCoords(x,y));
            for(auto it = objectsInCell.begin(); it != objectsInCell.end(); ++it)
            {
                CMapObject* mapObject = (*it);
                if(mapObject && mapObject->getBlockMode() != ENMapObjectBlockMode::notBlock)
                {
                    std::vector<CCellCoords> blockedCells;
                    mapObject->getBlockedCells(blockedCells);
                    for(auto cellsIt = blockedCells.begin(); cellsIt != blockedCells.end(); ++cellsIt)
                    {
                        CCellCoords& coords = (*cellsIt);
                        blockMap[coords.row][coords.col] = true;
                    }
                }
                
            }
        }
    }
}

void CMap::updateTileMap(const CCellCoords& leftDownCorner, const CCellCoords& rightUpCorner)
{
        
}

void CMap::generateTileMap(const CMapGenerateParams& params)
{
    CHeightMapGenerator generator;
    unsigned int maxDim = width;
    if(height > maxDim) maxDim = height;
    heightMap = generator.generateHeightMap(maxDim, 101);
    
    CTileData defaultTile(ENBioms::GRASS);   
    for(unsigned int row = 0; row < height; row++)
    {
        for(unsigned int col = 0; col < width; col++)
        {
            float height = heightMap->get(col, row);
            if(height > heightMap->getAverageValue() * 3 )      tileMap[row][col]  = CTileData(ENBioms::LAVA);
            else if(height > heightMap->getAverageValue() * 2 ) tileMap[row][col]  = CTileData(ENBioms::SNOW);
            else if(height > heightMap->getAverageValue() )     tileMap[row][col]  = CTileData(ENBioms::DESERT);
            else if(height > 0.0f )                             tileMap[row][col]  = CTileData(ENBioms::GRASS);
            else                                                tileMap[row][col]  = CTileData(ENBioms::WATER);
            
            blockMap[row][col] = false;
        }
    }
}

unsigned int CMap::getMoveWeight(const CCellCoords& cell, const CMovableObject* object) const
{
    if(cell.col >= width || cell.row >= height) return std::numeric_limits<unsigned int>::max();
    if(!object || !object->isValid() ) return std::numeric_limits<unsigned int>::max();
    
    CTileData& tile = tileMap[cell.row][cell.col];
    return object->getMoveCost(tile);
}

void CMap::update(const float dt)
{
    std::vector<CMapObject*> objects = objectsOnMap.getObjectsPool().getObjects();
    for(auto it = objects.begin(); it != objects.end(); ++it)
    {
        CMapObject* currMapObj = (*it);
        if(currMapObj->getIsNeedToUpdate()) currMapObj->update(dt);
    }
}

CMap::~CMap()
{
    delete heightMap;
    delete pathFinder;
    
    for(unsigned int i = 0; i < height; i++)
    {
        delete [] tileMap[i];
        delete [] blockMap[i];
    }
    delete [] tileMap;
    delete [] blockMap;
}
