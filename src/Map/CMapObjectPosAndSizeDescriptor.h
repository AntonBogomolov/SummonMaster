#pragma once 

#include <stdint.h>
#include "utils.h"

class CMapObjectPosAndSizeDescriptor
{
public:
    CMapObjectPosAndSizeDescriptor(const uint16_t xCenter = CMetrics::cellCenterX, const uint16_t yCenter = CMetrics::cellCenterY,
                                   const uint16_t rotation = 0, const uint16_t width = CMetrics::cellWidth, const uint16_t height = CMetrics::cellHeight,
                                   const uint16_t xRotCenter = CMetrics::cellWidth / 2, const uint16_t yRotCenter = CMetrics::cellHeight / 2
                                   ) : 
                                   xCenter(xCenter), yCenter(yCenter), width(width), height(height), 
                                   xRotCenter(xRotCenter), yRotCenter(yRotCenter), rotation(rotation)
    {
      
    }
    CMapObjectPosAndSizeDescriptor(const CMapObjectPosAndSizeDescriptor& descr)
    {
        this->xCenter = descr.xCenter;
        this->yCenter = descr.yCenter;
        this->width = descr.width;
        this->height = descr.height;
        this->xRotCenter = descr.xRotCenter;
        this->yRotCenter = descr.yRotCenter;
        this->rotation = descr.rotation;
    }
    ~CMapObjectPosAndSizeDescriptor()
    {
        
    }
public:    
    uint16_t  xCenter;
    uint16_t  yCenter;
    uint16_t  width;
    uint16_t  height;
    uint16_t  xRotCenter;
    uint16_t  yRotCenter;
    uint16_t  rotation;
};