#include "CGameRequestHandler.h"

#include "CSyncHelper.h"
#include "src/Net/CSummonMasterUser.h"
#include "src/Objects/CSpawner.h"

#include "novemberlib/utils/json.h"
using nlohmann::json;

CGameResponce CGameRequestHandler::executeRequest(CGameRequest& request)
{
    CGameResponce nullResponce(request, nullptr);
    /*
    if(!request.getIsValid()) return nullResponce;
    const CSummonMasterUser* user = request.user;
    
    const ENGameRequest requestType = request.getParams().getType();
    if(requestType == ENGameRequest::GetMapDescription)
    {
        json result;
        
        
    }else
    if(requestType == ENGameRequest::GetMapData)
    {
        try
        {
            const CGetMapDataRequestParam& params = static_cast<const CGetMapDataRequestParam&>(request.getParams());
        }
        catch(...)
        {
            return nullResponce;
        }
        
    }
    */
    return nullResponce;
}