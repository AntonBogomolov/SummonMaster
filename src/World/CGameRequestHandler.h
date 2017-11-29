#pragma once 

#include <novemberlib/utils/json.h>
using nlohmann::json;

#include "src/Net/CGameRequest.h"
#include "src/Net/CGameResponce.h"

class CSummonMasterUser;

class CGameRequestHandler
{
public:
    CGameRequestHandler()
    {
        
    }
    ~CGameRequestHandler()
    {
        
    }
    
    CGameResponce executeRequest(CGameRequest& request) const;
    
protected:
    void getInstancesList(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void getInstanceDescription(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void getMapData(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    
    void getObject(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void getObjects(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void setPathTarget(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
};