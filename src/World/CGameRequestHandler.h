#pragma once 

#include "src/Net/CGameRequest.h"
#include "src/Net/CGameResponce.h"

class CGameRequestHandler
{
public:
    CGameRequestHandler()
    {
        
    }
    ~CGameRequestHandler()
    {
        
    }
    
    CGameResponce executeRequest(CGameRequest& request);
protected:
    
};