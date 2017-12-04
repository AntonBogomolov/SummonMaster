#pragma once 

#include <stdint.h>
#include <queue>
#include <limits>
#include <cmath>

#include "CCellCoords.h"
#include "src/IJSONSerializable.h"

class CPathNode
{
public:
    unsigned int row;
    unsigned int col;
    long cost;  
    bool isValid;

    CPathNode(const CPathNode& node)
    {
        this->row = node.row;
        this->col = node.col;
        this->cost = node.cost;
        this->isValid = node.isValid;
    }
    CPathNode(const unsigned int row, const unsigned int col, const long cost = 0) 
                : row(row), col(col), cost(cost), isValid(true)
    {
        
    }
    bool operator < (const CPathNode &node) const
    {
        return this->cost > node.cost;
    }

    bool operator == (const CPathNode &node) const 
    {
        if(this->row == node.row && this->col == node.col) return true;
        return false;
    }
    
    long getFlatIndex(const unsigned int width) const
    {
        return row * width + col;
    }
    
    static unsigned int heuristic(const CPathNode &n1, const CPathNode &n2)
    {
        return std::abs(n1.row - n2.row) + std::abs(n1.col - n2.col);
    }
protected:
   
};

class CPathOnMap : public IJSONSerializable
{
public:
    CPathOnMap(std::queue<CPathNode>& path)
    {
        this->path = std::move(path);
    }
    CPathOnMap(const CPathOnMap& pathOnMap)
    {
        this->path = pathOnMap.path;
    }
    CPathOnMap(CPathOnMap&& that) 
    {
        this->path = std::move(that.path);
    }
    CPathOnMap() 
    {
        this->path = std::queue<CPathNode>();
    }
    ~CPathOnMap()
    {
        
    } 
    
    CPathOnMap& operator=(const CPathOnMap& pathOnMap)
    {
        this->path = pathOnMap.path;
        return *this;
    }

    bool getIsEmpty() const
    {
        return path.empty();
    }

    long getPathCost() const
    {
        long cost = 0;
        
        std::queue<CPathNode> tmpQueue = path;
        while(!tmpQueue.empty())
        {
            cost += tmpQueue.front().cost;
            tmpQueue.pop();
        }
        return cost;
    }
    
    virtual const json toJSON() const
    {
        json result = json::array();
                
        std::queue<CPathNode> tmpQueue = path;
        while(!tmpQueue.empty())
        {
            CPathNode& currNode = tmpQueue.front();
            tmpQueue.pop();
            result.push_back(json{{"row", currNode.row},{"col", currNode.col},{"cost", currNode.cost}});
        }
        return result;
    }
public:
    std::queue<CPathNode> path;
};

class CMap;
class CMovableObject;
class CPathFinder
{
public:
    CPathFinder(const CMap* map);    
    virtual ~CPathFinder()
    {
        
    }
    virtual CPathOnMap findPath(const CCellCoords& start, const CCellCoords& end, const CMovableObject* object) const = 0;
protected:
    unsigned int width;
    unsigned int height;
    const CMap* map;
};

class CPathFinderAStar : public CPathFinder
{
public:
    CPathFinderAStar(const CMap* map);    
    virtual ~CPathFinderAStar()
    {
        
    }
    virtual CPathOnMap findPath(const CCellCoords& start, const CCellCoords& end, const CMovableObject* object) const;
};


