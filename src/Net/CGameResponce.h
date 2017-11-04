#pragma once

#include "CGameRequest.h"
#include <novemberlib/utils/json.h>
using nlohmann::json;

class CGameRequest;

class CGameResponce
{
public:
    CGameResponce(const CGameRequest& request, std::vector<uint8_t>* binData)
    {
        this->request = request;
        this->binData = binData;
    }
    ~CGameResponce()
    {
        
    }
    
    const CGameRequest& getRequest() const
    {
        return request;
    }
    std::vector<uint8_t>* getBinData()
    {
        return binData;
    }
protected:
    const CGameRequest& request;
    std::vector<uint8_t>* binData;
};
