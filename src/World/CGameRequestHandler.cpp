#include "CGameRequestHandler.h"

#include <novemberlib/utils/CLog.h>
#include <novemberlib/utils/utils.h>

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
        json result;
        result["result"] = json::object();
        
        getMapData(user, request.getParams(), result);        
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
}

void CGameRequestHandler::getMapData(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    CInstanceManager& instanceManager = world->getInstanceManager();
    
    unsigned int mapId = params.getId();
    CInstance* instance = instanceManager.getInstanceForModify(mapId);
    if(!instance || instance->getIsLifeTimeEnd()) return;
    CMap* map = instance->getMapForModify();
    if(!map) return;
    
    bool**& blockMap     = map->getBlockMap();
    CTileData**& tileMap = map->getTileMap();
    const CGetMapDataRequestParam& mapParams = static_cast<const CGetMapDataRequestParam&>(params);
    
    unsigned int mapWidth = map->getWidth();
    unsigned int mapHeight= map->getHeight();
    if(mapParams.ldCorner.xCell > mapWidth - 1 || mapParams.ruCorner.xCell > mapWidth - 1) return;
    if(mapParams.ldCorner.yCell > mapHeight- 1 || mapParams.ruCorner.yCell > mapHeight- 1) return;
    if(mapParams.ldCorner.xCell < 0 || mapParams.ruCorner.xCell < 0) return;
    if(mapParams.ldCorner.yCell < 0 || mapParams.ruCorner.yCell < 0) return;
    
    std::vector<bool> blockMapPart = std::vector<bool>();
    std::vector<uint8_t> tileMapPart = std::vector<uint8_t>();
    if(mapParams.isNeedBlockMap) 
    {
        for(unsigned int row = mapParams.ldCorner.yCell; row <= mapParams.ruCorner.yCell; row++)
        {
            for(unsigned int col = mapParams.ldCorner.xCell; col <= mapParams.ruCorner.xCell; col++)
            {
                blockMapPart.push_back(blockMap[row][col]);
            }
        }
        
        result["result"]["blockData"] = json(std::move(blockMapPart));
    }   
    if(mapParams.isNeedTileMap)
    {
        for(unsigned int row = mapParams.ldCorner.yCell; row <= mapParams.ruCorner.yCell; row++)
        {
            for(unsigned int col = mapParams.ldCorner.xCell; col <= mapParams.ruCorner.xCell; col++)
            {
                tileMapPart.push_back(tileMap[row][col].getData());
            }
        }
        result["result"]["tileData"] = json(std::move(tileMapPart));
    }
    result["result"]["ldCorner"] = json{{"x", mapParams.ldCorner.xCell}, {"y", mapParams.ldCorner.yCell}};
    result["result"]["ruCorner"] = json{{"x", mapParams.ruCorner.xCell}, {"y", mapParams.ruCorner.yCell}};
    
    CLog::getInstance()->addInfo(result.dump());
}