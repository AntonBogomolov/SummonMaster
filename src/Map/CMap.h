#pragma once 

#include "src/Objects/CObject.h"
#include "CTileData.h"
#include "CObjectsOnMapCollection.h"
#include "src/Objects/CObjectsCollection.h"
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
    
    const CTileData& getTileAt(const unsigned int x, const unsigned int y) const
    {
        if(x < 0 || x >= width) return tileMap[0][0];
        if(y < 0 || y >= height)return tileMap[0][0];
        
        return tileMap[x][y];
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
        return blockMap[coords.xCell][coords.yCell];
    }
    
    virtual void update(const float dt)
    {
        
    }
       
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


