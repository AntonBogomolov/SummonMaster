#include "CGameRequestHandler.h"

#include "src/Net/CSummonMasterUser.h"
#include "src/Objects/CSpawner.h"

#include "CWorld.h"

CGameResponce CGameRequestHandler::executeRequest(CGameRequest& request)
{
    CGameResponce nullResponce(request, std::vector<uint8_t>());
    
    if(!request.getIsValid()) return nullResponce;
    CSummonMasterUser* user = request.getUserForModify();
        
    const ENGameRequest requestType = request.getParams().getType();
    if(requestType == ENGameRequest::GetInstanceDescription)
    {
        json result;
        result["result"] = json::object();
        
        getInstanceDescription(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }
    else
    if(requestType == ENGameRequest::GetInstancesList)
    {
        json result;
        result["result"] = json::array();
        
        getInstancesList(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }
    else
    if(requestType == ENGameRequest::GetMapData)
    {
        const CGetMapDataRequestParam& params = static_cast<const CGetMapDataRequestParam&>(request.getParams());
        json result;
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }
    
    return nullResponce;
}

void CGameRequestHandler::getInstancesList(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    CInstanceManager& instanceManager = world->getInstanceManager();
    
    std::map<unsigned int, CInstance*> instances = instanceManager.getInstances();
    for(auto it = instances.begin(); it != instances.end(); ++it)
    {
        const CInstance* currInst = it->second;
        if(currInst && currInst->getIsValid() && !currInst->getIsLifeTimeEnd())
        {
            json currInstanceJson = currInst->toJSON();
            result["result"].push_back(currInstanceJson);
        }
    }
}

void CGameRequestHandler::getInstanceDescription(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    CInstanceManager& instanceManager = world->getInstanceManager();
    
    unsigned int mapId = params.getId();
    const CInstance* instance = instanceManager.getInstance(mapId);
    if(!instance) return;
    result["result"] = instance->toJSON();    
    
//    const CMap* map = instance->getMap();
//    result["result"]["description"] = instance->getDescription();
//    result["result"]["width"] = map->getWidth();
//    result["result"]["height"]= map->getHeight();    
}

void CGameRequestHandler::getMapData(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    
}