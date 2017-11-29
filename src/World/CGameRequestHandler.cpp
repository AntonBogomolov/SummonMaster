#include "CGameRequestHandler.h"

#include <novemberlib/utils/CLog.h>
#include <novemberlib/utils/utils.h>

#include "src/Net/CSummonMasterUser.h"
#include "src/Objects/CSpawner.h"
#include "src/Objects/CMovableObject.h"

#include "CWorld.h"

CGameResponce CGameRequestHandler::executeRequest(CGameRequest& request) const
{
    CGameResponce nullResponce(request, std::vector<uint8_t>());
    
    if(!request.getIsValid()) return nullResponce;
    CSummonMasterUser* user = request.getUserForModify();
    
    json result;
    result["result"] = json::object();
        
    const ENGameRequest requestType = request.getParams().getType();
    if(requestType == ENGameRequest::GetObjects)
    {
        result["result"] = json::array();
        getObjects(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }else
    if(requestType == ENGameRequest::GetMapData)
    {
        getMapData(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }else
    if(requestType == ENGameRequest::GetObject)
    {
        getObject(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }else
    if(requestType == ENGameRequest::SetPathTarget)
    {
        setPathTarget(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }else
    if(requestType == ENGameRequest::GetInstanceDescription)
    {
        getInstanceDescription(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }
    else
    if(requestType == ENGameRequest::GetInstancesList)
    {
        result["result"] = json::array();
        getInstancesList(user, request.getParams(), result);        
        return CGameResponce(request, std::move(json::to_cbor(result)));
    }
    
    return nullResponce;
}

void CGameRequestHandler::getObject(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    const CInstanceManager& instanceManager = world->getInstanceManager();
    
    const CGetObjectRequestParam& objParams = static_cast<const CGetObjectRequestParam&>(params);
    
    unsigned int instanceId = objParams.instanceId;
    const CInstance* instance = instanceManager.getInstance(instanceId);
    if(!instance || instance->getIsLifeTimeEnd()) return;
    const CMap* map = instance->getMap();
    if(!map) return;
  
    unsigned int objId = objParams.getId();
    const std::unordered_map<unsigned int, CMapObject*>& objects = map->getObjectsOnMapCollection().getObjectsPool().getObjects();
    if(objects.find(objId) != objects.end())
    {
        result["result"] = objects.at(objId)->toJSON();
    }
}
void CGameRequestHandler::getObjects(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    const CInstanceManager& instanceManager = world->getInstanceManager();
    
    const CGetObjectsRequestParam& objParams = static_cast<const CGetObjectsRequestParam&>(params);
    
    unsigned int instanceId = objParams.instanceId;
    const CInstance* instance = instanceManager.getInstance(instanceId);
    if(!instance || instance->getIsLifeTimeEnd()) return;
    const CMap* map = instance->getMap();
    if(!map) return;
  
    unsigned int objId = objParams.getId();
    const std::unordered_map<unsigned int, CMapObject*>& objects = map->getObjectsOnMapCollection().getObjectsPool().getObjects();
    for(auto it = objects.begin(); it != objects.end(); ++it)
    {
        const CMapObject* currObj = it->second;
        const CCellCoords& cell = currObj->getCellCoords();
        if(cell.col < objParams.ldCorner.col && cell.col > objParams.ruCorner.col) continue;
        if(cell.row < objParams.ldCorner.row && cell.row > objParams.ruCorner.row) continue;
        
        if(currObj->getObject()->isFilterFit(objParams.tagFilter))
        {
            result["result"].push_back(currObj->toJSON());
        }
    }
}
void CGameRequestHandler::setPathTarget(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    CInstanceManager& instanceManager = world->getInstanceManagerForModify();
    
    const CSetPathTargetRequestParam& objParams = static_cast<const CSetPathTargetRequestParam&>(params);
    
    unsigned int instanceId = objParams.instanceId;
    CInstance* instance = instanceManager.getInstanceForModify(instanceId);
    if(!instance || instance->getIsLifeTimeEnd()) return;
    CMap* map = instance->getMapForModify();
    if(!map) return;
    
    if(objParams.target.col < 0 || objParams.target.col >= map->getWidth())  return;
    if(objParams.target.row < 0 || objParams.target.row >= map->getHeight()) return;
  
    unsigned int objId = objParams.getId();
    std::unordered_map<unsigned int, CMapObject*>& objects = map->getObjectsOnMapCollectionForModify().getObjectsPoolForModify().getObjectsForModify();
    if(objects.find(objId) != objects.end())
    {
        CMapObject* obj = objects.at(objId);
        CMovableObject* movableObject = dynamic_cast<CMovableObject*>(obj);
        if(!movableObject) return;
        movableObject->setPathTarget(objParams.target);
    }
}

void CGameRequestHandler::getInstancesList(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    const CInstanceManager& instanceManager = world->getInstanceManager();
    
    const std::map<unsigned int, CInstance*> instances = instanceManager.getInstances();
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
    const CInstanceManager& instanceManager = world->getInstanceManager();
    
    unsigned int mapId = params.getId();
    const CInstance* instance = instanceManager.getInstance(mapId);
    if(!instance) return;
    result["result"] = instance->toJSON();     
}

void CGameRequestHandler::getMapData(CSummonMasterUser* user, const CGameRequestParam& params, json& result) const
{
    CWorld* world = CWorld::getInstance();
    const CInstanceManager& instanceManager = world->getInstanceManager();
    
    unsigned int mapId = params.getId();
    const CInstance* instance = instanceManager.getInstance(mapId);
    if(!instance || instance->getIsLifeTimeEnd()) return;
    const CMap* map = instance->getMap();
    if(!map) return;
    
    //const bool**& blockMap     = map->getBlockMap();
    //const CTileData**& tileMap = map->getTileMap();
    const CGetMapDataRequestParam& mapParams = static_cast<const CGetMapDataRequestParam&>(params);
    
    unsigned int mapWidth = map->getWidth();
    unsigned int mapHeight= map->getHeight();
    if(mapParams.ldCorner.col > mapWidth - 1 || mapParams.ruCorner.col > mapWidth - 1) return;
    if(mapParams.ldCorner.row > mapHeight- 1 || mapParams.ruCorner.row > mapHeight- 1) return;
    if(mapParams.ldCorner.col < 0 || mapParams.ruCorner.col < 0) return;
    if(mapParams.ldCorner.row < 0 || mapParams.ruCorner.row < 0) return;
    
    std::vector<bool> blockMapPart = std::vector<bool>();
    std::vector<uint8_t> tileMapPart = std::vector<uint8_t>();
    if(mapParams.isNeedBlockMap) 
    {
        for(unsigned int row = mapParams.ldCorner.row; row <= mapParams.ruCorner.row; row++)
        {
            for(unsigned int col = mapParams.ldCorner.col; col <= mapParams.ruCorner.col; col++)
            {
                blockMapPart.push_back(map->getIsBlockAtFast(row, col));
            }
        }
        
        result["result"]["blockData"] = json(std::move(blockMapPart));
    }   
    if(mapParams.isNeedTileMap)
    {
        for(unsigned int row = mapParams.ldCorner.row; row <= mapParams.ruCorner.row; row++)
        {
            for(unsigned int col = mapParams.ldCorner.col; col <= mapParams.ruCorner.col; col++)
            {
                tileMapPart.push_back(map->getTileAtFast(row, col).getData());
            }
        }
        result["result"]["tileData"] = json(std::move(tileMapPart));
    }
    result["result"]["ldCorner"] = json{{"x", mapParams.ldCorner.col}, {"y", mapParams.ldCorner.row}};
    result["result"]["ruCorner"] = json{{"x", mapParams.ruCorner.col}, {"y", mapParams.ruCorner.row}};
    
    CLog::getInstance()->addInfo(result.dump());
}