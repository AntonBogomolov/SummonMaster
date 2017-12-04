#pragma once 

#include "src/utils.h"

class CCellCoords
{
public:
    unsigned int col;
    unsigned int row;
    
    CCellCoords()
    {
        
    }
    CCellCoords(const unsigned int col, const unsigned int row)
    {
        this->col = col;
        this->row = row;
    }
    CCellCoords(const CCellCoords& cell)
    {
        this->col = cell.col;
        this->row = cell.row;
    }
    ~CCellCoords()
    {
        
    }
    
    ENDirection getDirection(const CCellCoords& point) const 
    {
        if(col >  point.col && row >  point.row ) return ENDirection::UpLeft;
        if(col == point.col && row >  point.row ) return ENDirection::Up;
        if(col <  point.col && row >  point.row ) return ENDirection::UpRight;
        
        if(col >  point.col && row == point.row ) return ENDirection::Left;
        if(col == point.col && row == point.row ) return ENDirection::NONE;
        if(col <  point.col && row == point.row ) return ENDirection::Right;
        
        if(col >  point.col && row <  point.row ) return ENDirection::DownLeft;
        if(col == point.col && row <  point.row ) return ENDirection::Down;
        if(col <  point.col && row <  point.row ) return ENDirection::DownRight;
        
        return ENDirection::NONE;
    }
    
    bool operator <(const CCellCoords& rhs) const
    {
        if(col > rhs.col) return false;
        else
        if(col < rhs.col) return true;
        else
        {
            if(row < rhs.row) return true;
            else return false;
        }
    }
    
    bool operator ==(const CCellCoords& rhs) const
    {
        if(this->col == rhs.col && this->row == rhs.row) return true;
        return false;
    }
    bool operator !=(const CCellCoords& rhs) const
    {
        if(this->col != rhs.col || this->row != rhs.row) return true;
        return false;
    }
protected:
    
};

using namespace std;

namespace std 
{
    template <>
    class hash<CCellCoords>
    {
    public :
        size_t operator()(const CCellCoords &cell ) const
        {
            const int maxCoord = 10000;
            return cell.row * maxCoord + cell.col;
        }
    };
}