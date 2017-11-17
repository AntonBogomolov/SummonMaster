#pragma once

#include <stdint.h>

enum class ENBioms{ GRASS = 0, DESERT = 1, SNOW = 2, WATER = 3, LAVA = 4, WARFOG = 5};
enum class ENTileBorder{ NONE = 0, H_A = 1, H_B = 2, V_A = 3, V_B = 4, C_DR_A = 5, C_DR_B = 6,
                         C_DL_A = 7, C_DL_B = 8, C_UR_A = 9, C_UR_B = 10, C_UL_A = 11, C_UL_B = 12};

class CTileData
{
public:
    CTileData()
    {
        setTileBiom(ENBioms::GRASS);
        setTileBorder(ENTileBorder::NONE);
    }
    CTileData(  const ENBioms biom, const ENTileBorder border = ENTileBorder::NONE,
                bool isHasRoad = false, bool isHasRiver = false)
    {
        data = 0;
        setTileBiom(biom);
        setTileBorder(border);
        setIsHasRoad(isHasRoad);
        setIsHasRiver(isHasRiver);
    }
    CTileData(const CTileData& tile)
    {
        this->data = tile.getData();
    }
    ~CTileData()
    {
        
    }
    
    void setIsHasRoad(const bool hasRoad)  
    {
        if(hasRoad) data = (data | 0b0000000100000000);
        else        data = (data & 0b1111111011111111);
    }
    void setIsHasRiver(const bool hasRiver)   
    {
        if(hasRiver) data = (data | 0b0000001000000000);
        else         data = (data & 0b1111110111111111);
    }
    void setTileBiom(const ENBioms val)  
    {
        data = (data & 0xFFF0) | ((static_cast<uint16_t>(val)) & 0x000F);
    }
    void setTileBorder(const ENTileBorder val)  
    {
        data = (data & 0xFF0F) | (((static_cast<uint16_t>(val)) << 4) & 0x00F0);
    }
    ENBioms getTileBiom() const 
    {
        return static_cast<ENBioms>(data & 0x000F);
    }
    ENTileBorder getTileBorder() const 
    {
        return static_cast<ENTileBorder>((data & 0x00F0) >> 4 );
    }
    bool getIsHasRoad() const 
    {
        return ((data & 0b0000000100000000) >> 8);
    }
    bool getIsHasRiver() const 
    {
        return ((data & 0b0000001000000000) >> 9);
    }
    
    uint16_t getData() const 
    {
        return data;
    }
protected:
    uint16_t data;
};