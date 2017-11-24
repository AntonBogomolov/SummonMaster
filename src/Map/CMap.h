#pragma once 

#include "src/Objects/CObject.h"
#include "CTileData.h"
#include "CObjectsOnMapCollection.h"
#include "src/Objects/CObjectsCollection.h"
#include "CPathFinder.h"
#include "CEventDispatcher.h"
#include "IUpdatable.h"

#include "src/IJSONSerializable.h"

class CMapGenerateParams
{
public:
    CMapGenerateParams()
    {
        
    }
    ~CMapGenerateParams()
    {
        
    }
    
    float waterLevel;
};

class CMapCreationParams : public CObjectCreationParams
{
public:
    CMapCreationParams(const unsigned int width, const unsigned int height, CMapGenerateParams& generationParams) : 
                          CObjectCreationParams(ENObjectsType::MAP),
                          width(width), height(height), generationParams(generationParams)
    {
       
    }
    virtual ~CMapCreationParams()
    {
        
    }
    
    unsigned int width;
    unsigned int height;
    CMapGenerateParams generationParams;
protected:    
};

class CMovableObject;
class CHeightMap;
class CMap : public IEventHandler, public IUpdatable, public IJSONSerializable
{
public:
    friend class CInstance;
    CMap(const CMap& map) = delete;
    
    unsigned int getWidth() const
    {
        return width;
    }
    unsigned int getHeight() const
    {
        return height;
    }
    
    const CHeightMap* getHeightMap() const
    {
        return heightMap;
    }
    
    CTileData**& getTileMap()
    {
        return tileMap;
    }
    bool**& getBlockMap()
    {
        return blockMap;
    }
    const CTileData& getTileAtFast(const unsigned int row, const unsigned int col) const
    {
        return tileMap[row][col];
    }
    const bool getIsBlockAtFast(const unsigned int row, const unsigned int col) const
    {
        return blockMap[row][col];
    }
    
    const CTileData& getTileAt(const unsigned int row, const unsigned int col) const
    {
        if(col < 0 || col >= width) return tileMap[0][0];
        if(row < 0 || row >= height)return tileMap[0][0];
        
        return tileMap[row][col];
    }
    const bool getIsBlockAt(const unsigned int row, const unsigned int col) const
    {
        if(col < 0 || col >= width) return blockMap[0][0];
        if(row < 0 || row >= height)return blockMap[0][0];
        
        return blockMap[row][col];
    }
    const CObjectsCollection& getLocalObjectsTable() const
    {
        return localObjectsTable;
    }
    CObjectsCollection& getLocalObjectsTableForModify()
    {
        return localObjectsTable;
    }
    
    const CObjectsOnMapCollection& getObjectsOnMapCollection() const
    {
        return objectsOnMap;
    }
    CObjectsOnMapCollection& getObjectsOnMapCollection()
    {
        return objectsOnMap;
    }
    bool getIsTileBlocked(const CCellCoords& coords) const
    {
        return blockMap[coords.col][coords.row];
    }
    
    const CPathFinder& getPathFinder() const
    {
        return *pathFinder;
    }
    
    virtual void update(const float dt);    
    virtual unsigned int getMoveWeight(const CCellCoords& cell, const CMovableObject* object) const;
       
    virtual ~CMap();
    
    virtual const json toJSON() const
    {
        return json{
            {"width", width},
            {"height", height}
        };
    }
protected:
    CMap(const CMapCreationParams& param);

    void updateBlockMap(const CCellCoords& leftDownCorner, const CCellCoords& rightUpCorner);
    void updateTileMap(const CCellCoords& leftDownCorner, const CCellCoords& rightUpCorner);
    void generateTileMap(const CMapGenerateParams& params);

    CHeightMap* heightMap;
    CTileData** tileMap;
    bool** blockMap;
    CObjectsCollection localObjectsTable;
    CObjectsOnMapCollection objectsOnMap;
    unsigned int width;
    unsigned int height;
    CPathFinderAStar* pathFinder;
};

class CInvalidateMapEventParam : public CEventParam
{
public:
    CInvalidateMapEventParam(const CCellCoords& leftDownCorner, const CCellCoords& rightUpCorner) :
                             CEventParam(ENEvent::INVALIDATE_MAP_REGION)
    {
        this->leftDownCorner = leftDownCorner;
        this->rightUpCorner  = rightUpCorner;
    }   
    CInvalidateMapEventParam(const CInvalidateMapEventParam& param) : CEventParam(param)
    {
       
    }
    virtual ~CInvalidateMapEventParam()
    {
        
    }
    const CCellCoords& getLeftDownCorner() const
    {
        return leftDownCorner;
    }
    const CCellCoords& getRightUpCorner() const
    {
        return rightUpCorner;
    }
protected:
    CCellCoords leftDownCorner;
    CCellCoords rightUpCorner;
};


