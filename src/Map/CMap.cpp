#include "CMap.h"

#include "CHeightMap.h"
#include "CMapObject.h"

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
    
    generateTileMap(param.generationParams);
    updateBlockMap(CCellCoords(0,0), CCellCoords(width-1, height-1));
    
    setIsValid(true);
}

void CMap::updateBlockMap(const CCellCoords& leftDownCorner, const CCellCoords& rightUpCorner)
{
    for(unsigned int x = leftDownCorner.xCell; x <= rightUpCorner.xCell; ++x)
    {
        for(unsigned int y = leftDownCorner.yCell; y <= rightUpCorner.yCell; ++y)
        {
            std::vector<CMapObject*>& objectsInCell = objectsOnMap.getAllMapObjectInCell(CCellCoords(x,y));
            for(auto it = objectsInCell.begin(); it != objectsInCell.end(); ++it)
            {
                CMapObject* mapObject = (*it);
                if(mapObject && mapObject->getIsBlocking())
                {
                    std::vector<CCellCoords> blockedCells;
                    mapObject->getBlockedCells(blockedCells);
                    for(auto cellsIt = blockedCells.begin(); cellsIt != blockedCells.end(); ++cellsIt)
                    {
                        CCellCoords& coords = (*cellsIt);
                        blockMap[coords.xCell][coords.yCell] = true;
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
    heightMap = generator.generateHeightMap(width, 101);
    
    CTileData defaultTile = CTileData(ENBioms::GRASS, ENTileBorder::NONE);   
    for(unsigned int row = 0; row < height; row++)
    {
        for(unsigned int col = 0; col < width; col++)
        {
            tileMap[row][col]  = defaultTile;
            blockMap[row][col] = false;
        }
    }
}

CMap::~CMap()
{
    delete heightMap;
    
    for(unsigned int i = 0; i < height; i++)
    {
        delete [] tileMap[i];
        delete [] blockMap[i];
    }
    delete [] tileMap;
    delete [] blockMap;
    
}
