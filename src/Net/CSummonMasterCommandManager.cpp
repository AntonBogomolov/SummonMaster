#include "CSummonMasterCommandManager.h"

#include <novemberlib/novemberlib.h>
#include "CSummonMasterUser.h"

#include "src/World/CWorld.h"
#include "src/Net/CGameRequest.h"
#include "src/Net/CGameResponce.h"

#include <novemberlib/HTTPClient/CHTTPClient.h>
#include <novemberlib/utils/json.h>
using nlohmann::json;

CSummonMasterCommandManager::CSummonMasterCommandManager()
{
    lastMessageCreationTime = 0l;
}

CSummonMasterCommandManager::~CSummonMasterCommandManager()
{
    //dtor
}

CCommandResult CSummonMasterCommandManager::processCommand(CFCGIRequest* currRequest)
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
    const std::string command = request->get.get("command", "");
    CCommandResult result;
    result.setData("Not valid");

    if(command.size() == (size_t)0)
    {
        result.setIsValid(false);
        return result;
    }
    
    if (command == "getInstancesList")          return gameGetInstancesList(currRequest);
    if (command == "getInstanceDescription")    return gameGetInstanceDescription(currRequest);
    if (command == "getMapData")                return gameGetMapData(currRequest);

    if (command == "login")             return loginCommand(currRequest);
    if (command == "logout")            return logoutCommand(currRequest);
    
    result.setIsValid(false);
    return result;
}


CCommandResult CSummonMasterCommandManager::gameGetInstancesList(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("Not valid input data");
    time_t now;
    time(&now);
       
    if(!isUserIdentity(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    
    CWorld* world = CWorld::getInstance();
    CGameRequestParam gameRequestParams(ENGameRequest::GetInstancesList);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}

CCommandResult CSummonMasterCommandManager::gameGetMapData(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("Not valid input data");
    time_t now;
    time(&now);
       
    if(!isUserIdentity(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string mapIdStr = request->post.get("map_id", "");
    std::string ldXIdStr = request->post.get("ldX", "");
    std::string ldYIdStr  = request->post.get("ldY", "");
    std::string ruXIdStr = request->post.get("ruX", "");
    std::string ruYIdStr = request->post.get("ruY", "");
    unsigned int mapId = 0;
    unsigned int ldX = 0;
    unsigned int ldY = 0;
    unsigned int ruX = 0;
    unsigned int ruY = 0;
    CLog::getInstance()->addInfo(mapIdStr + " " + ldXIdStr + ldYIdStr + ruXIdStr + ruYIdStr);
    try
    {
        mapId = std::stoi(mapIdStr);
        ldX = std::stoi(ldXIdStr);
        ldY = std::stoi(ldYIdStr);
        ruX = std::stoi(ruXIdStr);
        ruY = std::stoi(ruYIdStr);
    }
    catch(...)
    {
        mapId = 0;
        ldX = 0;
        ldY = 0;
        ruX = 0;
        ruY = 0;
    }
    if(mapId == 0) return commandResult;
    
    
    
    CWorld* world = CWorld::getInstance();
    CGetMapDataRequestParam gameRequestParams(mapId, CCellCoords(ldX, ldY), CCellCoords(ruX, ruY));
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}

CCommandResult CSummonMasterCommandManager::gameGetInstanceDescription(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("Not valid input data");
    time_t now;
    time(&now);
       
    if(!isUserIdentity(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string instIdStr = request->post.get("instance_id", "");
    unsigned int instanceId = 0;
    try{ instanceId = std::stoi(instIdStr);}
    catch(...) {instanceId = 0;}
    if(instanceId == 0) return commandResult;
    
    CWorld* world = CWorld::getInstance();
    CGameRequestParam gameRequestParams(ENGameRequest::GetInstanceDescription, instanceId);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}


CCommandResult CSummonMasterCommandManager::loginCommand(CFCGIRequest* currRequest) const
{
	CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
	commandResult.setData("Not valid input data");

	std::string login = request->post.get("login", "");
	std::string pass  = request->post.get("pass", "");
	std::string newUserStr = request->post.get("newuser", "off");
	std::string returnPage = request->post.get("ret_page", "index");
	bool isNewUser = newUserStr == "newuser" ? 1 : 0;

	if (login.length() == (size_t)0 || pass.length() == (size_t)0) return commandResult;

	CSessionManager* sessionManager = CManagers::getInstance()->getSessionManager();
	if (isNewUser)
	{
		sessionManager->registerUser(currRequest, login, pass);
		CLog::getInstance()->addInfo("new user:" + login + " " + pass);
	}
	else
	{
		sessionManager->loginUser(currRequest, login, pass);
		CLog::getInstance()->addInfo("login:" + login + " " + pass);
	}

	commandResult.setIsSuccess(true);
	commandResult.setData("<meta http-equiv='refresh' content='0; url=?page=" + returnPage + "' />");
	return commandResult;
}

CCommandResult CSummonMasterCommandManager::logoutCommand(CFCGIRequest* currRequest) const
{
	CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
	commandResult.setData("Not valid input data");
	std::string returnPage = request->post.get("ret_page", "index");

	CSessionManager* sessionManager = CManagers::getInstance()->getSessionManager();
	sessionManager->logoutUser(currRequest);

	commandResult.setIsSuccess(true);
	commandResult.setData("<meta http-equiv='refresh' content='0; url=?page=" + returnPage + "' />");
	return commandResult;
}

const CFileDescriptor* CSummonMasterCommandManager::handleMediaFile(CFCGIRequest* currRequest) const
{
	CConfigHelper* gs = CConfigHelper::getInstance();
	std::string postParamName = "postfile";

    const CFileDescriptor* file = currRequest->getRequestForModify()->files->getFile(postParamName);
    if (file == NULL)
    {
        CLog::getInstance()->addError("NULL file: " + postParamName);
        return NULL;
    }
    if(!file->getIsValid())
    {
        CLog::getInstance()->addError("NOT VALID FILE!");
        return NULL;
    }

    const std::string fileName = file->getFullFileName();
    const std::string fileType = file->getFileMIME();
    long fileSize = file->getFileSize();
    const char* fileData = file->getFileData();

    if (fileSize == 0 || fileName == "" || fileData == 0 || (long)fileSize > gs->getLongParamValue("maxFileSize", 10485760l)) return NULL;

    std::string filePath = CManagers::getInstance()->getResourceManager()->saveFile(file->getFileMD5Cache(), fileType, fileSize, fileData);
    if (filePath.length() == 0) return NULL;

    return file;
}

const std::vector<const CFileDescriptor*> CSummonMasterCommandManager::handlePicFiles(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
    std::vector<const CFileDescriptor*> resultPics;

    std::string filesCntStr = request->post.get("pic_files_cnt", "");
	int filesCnt = 0;
	try
	{
        filesCnt = atoi(filesCntStr.c_str());
	}
	catch(...)
	{
        filesCnt = 0;
	}
	CConfigHelper* gs = CConfigHelper::getInstance();

	std::string postParamBaseName = "picfile";
	std::string attachStr = "";
	std::string path;
	for (int i = 0; i < filesCnt; i++)
	{
        std::string postParamName = postParamBaseName + valueToString(i);
		const CFileDescriptor* file = currRequest->getRequestForModify()->files->getFile(postParamName);
		if (file == NULL)
		{
			CLog::getInstance()->addError("NULL file: " + postParamName);
			continue;
		}
        if(!file->getIsValid())
        {
            CLog::getInstance()->addError("NOT VALID FILE!");
            continue;
        }

		const std::string fileName = file->getFullFileName();
		const std::string fileType = file->getFileMIME();
		long fileSize = file->getFileSize();
		const char* fileData = file->getFileData();

		if (fileSize == 0 || fileName == "" || fileData == 0 || (long)fileSize > gs->getLongParamValue("maxFileSize", 10485760l)) continue;
        std::string filePath = CManagers::getInstance()->getResourceManager()->saveFile(file->getFileMD5Cache(), fileType, fileSize, fileData);
		if (filePath.length() == 0) continue;

		resultPics.push_back(file);
	}
	return resultPics;
}
