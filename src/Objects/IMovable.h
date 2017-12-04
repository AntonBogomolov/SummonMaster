#pragma once 

class CTileData;
class IMovable
{
public:
    virtual float getMoveSpeed() const = 0;
    virtual unsigned int getMoveCost(const CTileData& tile) const = 0;
    
    bool getIsCanMove() const
    {
        return getMoveSpeed() > 0.0f;
    }
protected:
    
};