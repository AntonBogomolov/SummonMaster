#include "CGameRequestHandler.h"

#include "src/Net/CSummonMasterUser.h"
#include "src/Objects/CSpawner.h"

#include "CWorld.h"
#include "novemberlib/utils/json.h"
using nlohmann::json;

CGameResponce CGameRequestHandler::executeRequest(CGameRequest& request)
{
    CGameResponce nullResponce(request, std::vector<uint8_t>());
    
    if(!request.getIsValid()) return nullResponce;
    const CSummonMasterUser* user = request.getUser();
    CWorld* world = CWorld::getInstance();
    CInstanceManager& instanceManager = world->getInstanceManager();
    
    const ENGameRequest requestType = request.getParams().getType();
    if(requestType == ENGameRequest::GetMapDescription)
    {
        json result;
        unsigned int mapId = request.getParams().getId();
        const CInstance* instance = instanceManager.getInstance(mapId);
        if(!instance) return nullResponce;
        
        const CMap* map = instance->getMap();
        result["width"] = map->getWidth();
        result["height"]= map->getHeight();
        
        return CGameResponce(request, json::to_cbor(result));
    }
    else
    if(requestType == ENGameRequest::GetMapData)
    {
        const CGetMapDataRequestParam& params = static_cast<const CGetMapDataRequestParam&>(request.getParams());
        
        json result;
        unsigned int mapId = params.getId();
        const CInstance* instance = instanceManager.getInstance(mapId);
        if(!instance) return nullResponce;
        
        const CMap* map = instance->getMap();
        result["width"] = map->getWidth();
        result["height"]= map->getHeight();
        
        return CGameResponce(request, json::to_cbor(result));
    }
    
    return nullResponce;
}