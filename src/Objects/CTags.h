#pragma once

#include "CObjectContainer.h"

#include "novemberlib/interfaces/ITemplateSingleton.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

//enum class ENTags {HUMAN, UNDEAD, ANIMAL, SUMMON, PET};

class CTagMap : public ITemplateSingleton<CTagMap>
{
public:
    const std::string getTagDescription(const int tag) const 
    {
        if(tagsMap.find(tag) != tagsMap.end())
        {
            return tagsMap.at(tag);
        }
        return "NONE";
    }
    void init()
    {
        if(!isInit)
        { 
            readTagsFromFile();
        }
        isInit = true;
    }

    virtual ~CTagMap()
    {
        
    };
protected:
    std::map<const int, std::string> tagsMap;
    
    void readTagsFromFile()
    {
        std::string tmpStr = "";
        std::ifstream file;
        try
        {
            file.open("tags.conf");
            if(!file.is_open())
            {
                //CLog::getInstance()->addError("Cant open tags.conf");
                return;
            }

            int currId = 1;
            while(!file.eof())
            {
                std::getline(file, tmpStr);
                if(tmpStr.length() > 2)
                {
                    tagsMap.emplace(currId,  tmpStr);
                    currId++;
                }
            }
        }
        catch(...)
        {
            //CLog::getInstance()->addError("Cant read config.conf");
        }
        file.close();
    }
    
private:
    friend CTagMap* ITemplateSingleton::getInstance();
    bool isInit;
    
    CTagMap()
    {
        isInit = false;
        init();
    }
};

class CTags : public CObjectContainer<int>
{
public:
    CTags()
    {
        
    } 
    CTags(const CTags& tags) : CObjectContainer(tags)
    {
        
    }
    virtual ~CTags()
    {
        
    }

    virtual void addObject(const int obj)
    {
        if(!isHasTag(obj)) container.push_back(obj);
    }
    void removeTag(const int obj)
    {
        for(auto it = container.begin(); it != container.end();)
        {
            const int currObj = (*it);
            if(currObj == obj)
            {
                container.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    bool isHasTag(const int tag)
    {
        for(auto it = container.begin(); it != container.end(); ++it)
        {
            const int currObj = (*it);
            if(currObj == tag) return true;
        }
        return false;
    }
protected:
};