#pragma once 

#include <unordered_map>
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
            delete it->second;
        }
    }
    
    void addToPool(const unsigned int id, T* obj)
    {
        if(obj == nullptr) return;
        objects[id] = obj;
    }
    void deleteObject(T* obj)
    {
        for(auto it = objects.begin(); it != objects.end(); )
        {
            T* currObj = it->second;
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
    std::unordered_map<unsigned int, T*>& getObjectsForModify()
    {
        return objects;
    }
    const std::unordered_map<unsigned int, T*>& getObjects() const
    {
        return objects;
    }
protected:
    //std::vector<T*> objects;
    std::unordered_map<unsigned int, T*> objects;
};