#pragma once

#include <stdint.h>

enum class ENBioms{ GRASS = 0, DESERT = 1, SNOW = 2, WATER = 3, LAVA = 4};
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
    CTileData(const ENBioms biom, const ENTileBorder border)
    {
        setTileBiom(biom);
        setTileBorder(border);
    }
    CTileData(const CTileData& tile)
    {
        this->data = tile.getData();
    }
    ~CTileData()
    {
        
    }
    
    void setTileBiom(const ENBioms val)  
    {
        data = (data & 0xF0) | ((static_cast<uint8_t>(val)) & 0x0F);
    }
    void setTileBorder(const ENTileBorder val)  
    {
        data = (data & 0x0F) | (((static_cast<uint8_t>(val)) << 4) & 0xF0);
    }
    ENBioms getTileBiom() const 
    {
        return static_cast<ENBioms>(data & 0x0F);
    }
    ENTileBorder getTileBorder() const 
    {
        return static_cast<ENTileBorder>((data & 0xF0) >> 4 );
    }
    
    uint8_t getData() const 
    {
        return data;
    }
protected:
    uint8_t data;
};