#pragma once 

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