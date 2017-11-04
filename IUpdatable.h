#pragma once

class IUpdatable
{
public:
    IUpdatable(){isNeedToUpdate = false;};
    virtual ~IUpdatable(){};
    virtual void update(const float dt)  = 0;
    
    void setIsNeedToUpdate(const bool isNeedToUpdate)
    {
        this->isNeedToUpdate = isNeedToUpdate;
    }
    bool getIsNeedToUpdate() const
    {
        return isNeedToUpdate;
    }
protected:
    bool isNeedToUpdate;
};