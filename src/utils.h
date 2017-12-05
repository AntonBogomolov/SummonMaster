#pragma once

#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <novemberlib/interfaces/ITemplateSingleton.h>
#include <novemberlib/utils/utils.h>
#include <novemberlib/utils/md5.h>

class CUtils : public ITemplateSingleton<CUtils>
{
public:
    void initRandom(const unsigned int seed = 0)
    {
        if(seed == 0)
        {
            rndSeed = time(0);
            srand(rndSeed);
        }
        else
        {
            rndSeed = seed;
            srand(rndSeed); 
        }
        isRndInit = true;
    }
    unsigned int getRandomNumber(const unsigned int minNumber = 0, const unsigned int maxNumber = UINT32_MAX)
    {
        if(!isRndInit) initRandom();
        if(minNumber > maxNumber) return 0;    
        return minNumber + rand() % (maxNumber - minNumber);
    }
    
    void rotatePointRelative(int& x, int& y, const float angle, const int cx = 0, const int cy = 0)
    {
        int oldX = x;
        int oldY = y;
        float rad = (angle * 3.1415f) / 180.0f;
        
        x = cx + (oldX - cx) * cos(rad) - (oldY - cy) * sin(rad);
        y = cy + (oldY - cy) * cos(rad) + (oldX - cx) * sin(rad);
    }
    
    std::string genHashKey(const std::string& data)
    {
        return md5(data);
    }
    std::string genRndHashKey()
    {
        return md5(valueToString(getRandomNumber()));
    }
    
    virtual ~CUtils(){};
protected:
    bool isRndInit;
    unsigned int rndSeed;
private:
    friend CUtils* ITemplateSingleton::getInstance();
    CUtils()
    {
        isRndInit = false;
        rndSeed = 0;
    }
};

enum class ENDirection { Up = 0, Down = 1, Right = 2, Left = 3, UpRight = 4, UpLeft = 5, DownRight = 6, DownLeft = 7, NONE = 8 }; 

class CMetrics
{
public:
    static const uint16_t cellWidth  = 128;
    static const uint16_t cellHeight = 128;
    static const uint16_t cellCenterX = cellWidth / 2;
    static const uint16_t cellCenterY = cellHeight / 2;
    static const uint16_t baseMoveCost = 10;
    static const uint16_t baseMoveSpeed = 10;
};

