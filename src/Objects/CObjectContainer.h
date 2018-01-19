#pragma once

#include <vector>

template<typename T>
class CObjectContainer
{
public:
    CObjectContainer()
    {
    }
    CObjectContainer(const CObjectContainer& cont)
    {
        const std::vector<T>& objects = cont.getContainer();
        for(auto it = objects.begin(); it != objects.end(); ++it)
        {
            addObject(*it);
        }
    }
    
    virtual ~CObjectContainer()
    {
      
    }

    virtual void addObject(const T& obj)
    {
        container.push_back(obj);
    }
    const std::vector<T>& getContainer() const
    {
        return container;
    }
    std::vector<T>& getContainerForModify()
    {
        return container;
    }
    const T& getObjectAt(const int index, const T& defaultObj = T()) const
    {
        if(container.size() >= index) return defaultObj;
        return container.at(index);
    }
    long getSize() const
    {
        return container.size();
    }
    
    void clear()
    {
        container.clear();
    }
protected:
    std::vector<T> container;
};