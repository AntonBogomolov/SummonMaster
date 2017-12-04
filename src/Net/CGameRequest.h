#pragma once

#include "src/Map/CCellCoords.h"
#include "src/Objects/CTags.h"

enum class ENGameRequest {GetInstancesList, GetMapData, GetInstanceDescription, GetMapObject, GetMapObjects, SetPathTarget, GetPlayer, LoginPlayer};

class CGameRequestParam
{
public:
    CGameRequestParam(const ENGameRequest& type, const unsigned int id = 0) : type(type), id(id)
    {
        
    }
    virtual ~CGameRequestParam()
    {
        
    }
    const ENGameRequest getType() const
    {
        return type;
    }
    const unsigned int getId() const
    {
        return id;
    }
protected:
    ENGameRequest type;
    unsigned int id;
};

class CGetMapDataRequestParam : public CGameRequestParam
{
public:
    CGetMapDataRequestParam(const unsigned int mapId, const CCellCoords& ldCorner, const CCellCoords& ruCorner,
                            const bool isNeedBlockMap = true, bool isNeedTileMap = true) : CGameRequestParam(ENGameRequest::GetMapData, mapId),
                            mapId(mapId), ldCorner(ldCorner), ruCorner(ruCorner), isNeedBlockMap(isNeedBlockMap), isNeedTileMap(isNeedTileMap)
    {
        
    }
    virtual ~CGetMapDataRequestParam()
    {
        
    }
   
public:
    unsigned int mapId;
    CCellCoords ldCorner;
    CCellCoords ruCorner;
    bool isNeedBlockMap;
    bool isNeedTileMap; 
};

class CSetPathTargetRequestParam : public CGameRequestParam
{
public:
    CSetPathTargetRequestParam(const unsigned int instanceId, const unsigned int objectId, const CCellCoords& target) 
                                : CGameRequestParam(ENGameRequest::SetPathTarget, objectId),
                                instanceId(instanceId), target(target)
    {
        
    }
    virtual ~CSetPathTargetRequestParam()
    {
        
    }
   
public:
    unsigned int instanceId;
    CCellCoords target;
};

class CGetMapObjectRequestParam : public CGameRequestParam
{
public:
    CGetMapObjectRequestParam(const unsigned int instanceId, const unsigned int objectId) 
                                : CGameRequestParam(ENGameRequest::GetMapObject, objectId),
                                instanceId(instanceId)
    {
        
    }
    virtual ~CGetMapObjectRequestParam()
    {
        
    }
   
public:
    unsigned int instanceId;
};

class CGetPlayerRequestParam : public CGameRequestParam
{
public:
    CGetPlayerRequestParam(const unsigned int objectId) : CGameRequestParam(ENGameRequest::GetPlayer, objectId)
    {
        
    }
    virtual ~CGetPlayerRequestParam()
    {
        
    }
};

class CGetMapObjectsRequestParam : public CGameRequestParam
{
public:
    CGetMapObjectsRequestParam(const unsigned int instanceId, const CCellCoords& ldCorner, const CCellCoords& ruCorner, 
                               const CTagFilter& tagFilter) 
                                : CGameRequestParam(ENGameRequest::GetMapObjects, instanceId),
                                instanceId(instanceId), ldCorner(ldCorner), ruCorner(ruCorner), tagFilter(tagFilter)
    {
        
    }
    virtual ~CGetMapObjectsRequestParam()
    {
        
    }
   
public:
    unsigned int instanceId;
    CCellCoords ldCorner;
    CCellCoords ruCorner;
    CTagFilter tagFilter;
};


class CSummonMasterUser;
class CGameRequest
{
public:
    CGameRequest(CSummonMasterUser* user, const CGameRequestParam& params, const long requestCreationTime) 
                 : user(user), params(params), requestCreationTime(requestCreationTime)
    {
        if(this->user == nullptr) this->isValid = false;
    }
    CGameRequest(const CGameRequest& request)
                : user(request.getUser()), params(request.getParams()), requestCreationTime(request.getCreationTime())
    {
        if(this->user == nullptr) this->isValid = false;
    }
    virtual ~CGameRequest()
    {
        
    }
    CSummonMasterUser* getUser() const 
    {
        return user;
    }
    CSummonMasterUser* getUserForModify() 
    {
        return user;
    }
    const CGameRequestParam& getParams() const 
    {
        return params;
    }
    long getCreationTime() const 
    {
        return requestCreationTime;
    }
    bool getIsValid() const
    {
        return isValid;
    }
protected:
    CSummonMasterUser* user;
    const CGameRequestParam& params;
    long requestCreationTime;
    
    bool isValid;
};
