#pragma once 

class CCellCoords
{
public:
    unsigned int xCell;
    unsigned int yCell;
    
    CCellCoords()
    {
        
    }
    CCellCoords(const unsigned int xCell, const unsigned int yCell)
    {
        this->xCell = xCell;
        this->yCell = yCell;
    }
    CCellCoords(const CCellCoords& cell)
    {
        this->xCell = cell.xCell;
        this->yCell = cell.yCell;
    }
    ~CCellCoords()
    {
        
    }
    
    bool operator <(const CCellCoords& rhs) const
    {
        if(xCell > rhs.xCell) return false;
        else
        if(xCell < rhs.xCell) return true;
        else
        {
            if(yCell < rhs.yCell) return true;
            else return false;
        }
    }
protected:
    
};