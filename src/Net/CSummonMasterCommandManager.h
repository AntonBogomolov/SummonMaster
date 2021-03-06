#ifndef CSITECOMMANDMANAGER_H
#define CSITECOMMANDMANAGER_H

#include "novemberlib/managers/CCommandsManager.h"
#include <vector>

class CFCGIRequest;
class CFileDescriptor;

class CSummonMasterCommandManager : public CCommandsManager
{
    public:
        virtual CCommandResult processCommand(CFCGIRequest* currRequest);
        
        CCommandResult gameGetInstancesList(CFCGIRequest* currRequest) const;
        CCommandResult gameGetInstanceDescription(CFCGIRequest* currRequest) const;
        CCommandResult gameGetMapData(CFCGIRequest* currRequest) const;
        CCommandResult gameGetMetrics(CFCGIRequest* currRequest) const;
        
        CCommandResult gameGetMapObject(CFCGIRequest* currRequest) const;
        CCommandResult gameGetMapObjects(CFCGIRequest* currRequest) const;
        CCommandResult gameSetPathTarget(CFCGIRequest* currRequest) const;
        
        CCommandResult gameGetPlayer(CFCGIRequest* currRequest) const;
        CCommandResult gameCreatePlayer(CFCGIRequest* currRequest) const;
        CCommandResult gameLoginPlayer(CFCGIRequest* currRequest) const;
        CCommandResult gameLogoutPlayer(CFCGIRequest* currRequest) const;
      
        CCommandResult loginCommand(CFCGIRequest* currRequest) const;
        CCommandResult logoutCommand(CFCGIRequest* currRequest) const;

        CSummonMasterCommandManager();
        virtual ~CSummonMasterCommandManager();
    protected:
        mutable long lastMessageCreationTime;       
    private:
        const CFileDescriptor* handleMediaFile(CFCGIRequest* currRequest) const;
        const std::vector<const CFileDescriptor*> handlePicFiles(CFCGIRequest* currRequest) const;
        bool identAndCheckUser(CFCGIRequest* currRequest) const;
};

#endif // CSITECOMMANDMANAGER_H
