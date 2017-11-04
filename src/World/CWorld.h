#pragma once 

#include "novemberlib/interfaces/ITemplateSingleton.h"
#include "CGameRequestHandler.h"

class CWorld : public ITemplateSingleton<CWorld>
{
public:
    virtual ~CWorld();
    
    CGameRequestHandler& getRequestHandler() 
    {
        return requestHandler;
    }
protected:
    CGameRequestHandler requestHandler;
private:
    CWorld();    
    friend CWorld* ITemplateSingleton::getInstance();
};