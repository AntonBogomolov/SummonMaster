#pragma once

#include "CGameRequest.h"
#include <novemberlib/utils/json.h>
using nlohmann::json;

class CGameResponce
{
public:
    CGameResponce(const CGameRequest& request, std::vector<uint8_t> binData) : request(request), binData(std::move(binData))
    {

    }
    CGameResponce(const CGameResponce& that) = delete;
    CGameResponce& operator = (const CGameResponce& that) = delete;
    
    CGameResponce(CGameResponce&& that) : request(that.getRequest())
    {
        this->binData = std::move(that.getBinData());
    }
    ~CGameResponce()
    {
        
    }
    
    const CGameRequest& getRequest() const
    {
        return request;
    }
    std::vector<uint8_t>& getBinData()
    {
        return binData;
    }
protected:
    const CGameRequest& request;
    std::vector<uint8_t> binData;
};
