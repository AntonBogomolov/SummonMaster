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
    void getMetrics(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    
    void getMapObject(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void getMapObjects(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void setPathTarget(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    
    void getPlayer(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void loginPlayer(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void logoutPlayer(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
    void createPlayer(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const;
};