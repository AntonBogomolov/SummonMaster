#pragma once

#include "CCellCoords.h"

enum class ENGameRequest { GetMapData, GetMapDescription, GetObject };

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
    CCellCoords ldCorner;
    CCellCoords ruCorner;
    bool isNeedBlockMap;
    bool isNeedTileMap;    
};

class CSummonMasterUser;
class CGameRequest
{
public:
    CGameRequest(const CSummonMasterUser* user, const CGameRequestParam* params, const long requestCreationTime) 
                 : user(user), params(params), requestCreationTime(requestCreationTime)
    {
        if(this->user == nullptr) this->isValid = false;
    }
    CGameRequest(const CGameRequest& request)
                : user(request->getUser()), params(request->getParams()), requestCreationTime(request->getCreationTime())
    {
        if(this->user == nullptr) this->isValid = false;
    }
    virtual ~CGameRequest()
    {
        
    }
    const CSummonMasterUser* getUser() const 
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
