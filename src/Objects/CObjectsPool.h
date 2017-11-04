#pragma once 

#include <vector>

template<class T> 
class CObjectsPool
{
public:
    CObjectsPool()
    {
        
    }
    ~CObjectsPool()
    {
        for(auto it = objects.begin(); it != objects.end(); ++it)
        {
            delete (*it);
        }
    }
    
    void addToPool(T* obj)
    {
        if(obj == nullptr) return;
        
        objects.push_back(obj);
    }
    void deleteObject(T* obj)
    {
        for(auto it = objects.begin(); it != objects.end(); )
        {
            T* currObj = (*it);
            if(currObj == obj)
            {
                delete currObj;
                objects.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    std::vector<T*>& getObjects()
    {
        return objects;
    }
protected:
    std::vector<T*> objects;
};