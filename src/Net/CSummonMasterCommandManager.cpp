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
    if (command == "getMapObject")              return gameGetMapObject(currRequest);
    if (command == "getMapObjects")             return gameGetMapObjects(currRequest);
    if (command == "setPathTarget")             return gameSetPathTarget(currRequest);
    if (command == "getPlayer")                 return gameGetPlayer(currRequest);
    if (command == "createPlayer")              return gameCreatePlayer(currRequest);
    if (command == "loginPlayer")               return gameLoginPlayer(currRequest);
    if (command == "logoutPlayer")              return gameLogoutPlayer(currRequest);
    if (command == "getMetrics")                return gameGetMetrics(currRequest);

    if (command == "login")             return loginCommand(currRequest);
    if (command == "logout")            return logoutCommand(currRequest);
    
    result.setIsValid(false);
    return result;
}

CCommandResult CSummonMasterCommandManager::gameGetMetrics(CFCGIRequest* currRequest) const
{
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
    
   	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    CWorld* world = CWorld::getInstance();
    CGetMetricsRequestParam gameRequestParams;
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}
CCommandResult CSummonMasterCommandManager::gameGetPlayer(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
    
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string playerKey  = request->post.get("key", "");
    if(playerKey.length() < 4) return commandResult;   
    
    CWorld* world = CWorld::getInstance();
    CGetPlayerRequestParam gameRequestParams(playerKey);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}
CCommandResult CSummonMasterCommandManager::gameCreatePlayer(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
    
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
    CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    
    std::string playerName  = request->post.get("name", "");
    if(playerName.length() < 2) return commandResult;   
    
    CWorld* world = CWorld::getInstance();
    CCreatePlayerRequestParam gameRequestParams(playerName);
    CGameRequest  gameRequest(user, gameRequestParams, now);

    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}
CCommandResult CSummonMasterCommandManager::gameLoginPlayer(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
       
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string playerKey  = request->post.get("key", "");
    if(playerKey.length() < 4) return commandResult;   
    std::string instIdStr = request->post.get("instance_id", "");
    
    unsigned int instanceId = 0;
    try{ instanceId = std::stoi(instIdStr);}
    catch(...) {instanceId = 0;}
    if(instanceId == 0) return commandResult;
    
    CWorld* world = CWorld::getInstance();
    CLoginPlayerRequestParam gameRequestParams(playerKey, instanceId);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}
CCommandResult CSummonMasterCommandManager::gameLogoutPlayer(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
       
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string playerKey  = request->post.get("key", "");
    if(playerKey.length() < 4) return commandResult;   
    
    CWorld* world = CWorld::getInstance();
    CLogoutPlayerRequestParam gameRequestParams(playerKey);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}

CCommandResult CSummonMasterCommandManager::gameGetMapObject(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
       
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
	CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string objIdStr  = request->post.get("object_id", "");
    std::string instIdStr = request->post.get("instance_id", "");
    unsigned int instanceId = 0;
    unsigned int objId = 0;
    try{ objId = std::stoi(objIdStr); instanceId = std::stoi(instIdStr);}
    catch(...) {objId = 0;instanceId = 0;}
    if(objId == 0 || instanceId == 0) return commandResult;
    
    CWorld* world = CWorld::getInstance();
    CGetMapObjectRequestParam gameRequestParams(instanceId, objId);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}
CCommandResult CSummonMasterCommandManager::gameGetMapObjects(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
    CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
       
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
    CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string instanceIdStr = request->post.get("instance_id", "");
    std::string filterModeStr = request->post.get("filter_mode", "");
    std::string filterTags = request->post.get("filter_tags", "");
    std::string ldXIdStr = request->post.get("ldX", "");
    std::string ldYIdStr  = request->post.get("ldY", "");
    std::string ruXIdStr = request->post.get("ruX", "");
    std::string ruYIdStr = request->post.get("ruY", "");
    unsigned int filterMode = 1;
    unsigned int instanceId = 0;
    unsigned int ldX = 0;
    unsigned int ldY = 0;
    unsigned int ruX = 0;
    unsigned int ruY = 0;
    try
    {
        instanceId = std::stoi(instanceIdStr);
        filterMode = std::stoi(filterModeStr);
        ldX = std::stoi(ldXIdStr);
        ldY = std::stoi(ldYIdStr);
        ruX = std::stoi(ruXIdStr);
        ruY = std::stoi(ruYIdStr);
    }
    catch(...)
    {
        instanceId = 0;
        filterMode = 1;
        ldX = 0;
        ldY = 0;
        ruX = 0;
        ruY = 0;
    }
    if(instanceId == 0) return commandResult;
    
    CTagFilter tagFilter;
    if(filterMode == 0) tagFilter.filterMode = ENTagFilterMode::And;
    if(filterMode == 1) tagFilter.filterMode = ENTagFilterMode::Or;
    if(filterMode == 2) tagFilter.filterMode = ENTagFilterMode::Not;
    std::vector<std::string> tagsIdsStr;
    split(tagsIdsStr, filterTags, ",");
    for(auto it = tagsIdsStr.begin(); it != tagsIdsStr.end(); ++it)
    {
        int currTagId = -1;
        try{ currTagId = std::stoi(*it);}
        catch(...){currTagId = -1;}
        if(currTagId != -1) tagFilter.tags.addTag(currTagId);
    }
    
    CWorld* world = CWorld::getInstance();
    CGetMapObjectsRequestParam gameRequestParams(instanceId, CCellCoords(ldX, ldY), CCellCoords(ruX, ruY), tagFilter);
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}
CCommandResult CSummonMasterCommandManager::gameSetPathTarget(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
    CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
       
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
    CSummonMasterUser* user = dynamic_cast<CSummonMasterUser*>(currRequest->getUserForModify());
    std::string instanceIdStr = request->post.get("instance_id", "");
    std::string objectIdStr = request->post.get("object_id", "");
    std::string targetXStr  = request->post.get("targetX", "");
    std::string targetYStr  = request->post.get("targetY", "");
    unsigned int objectId = 0;
    unsigned int instanceId = 0;
    unsigned int targetX = 0;
    unsigned int targetY = 0;
    try
    {
        instanceId = std::stoi(instanceIdStr);
        objectId = std::stoi(objectIdStr);
        targetX = std::stoi(targetXStr);
        targetY = std::stoi(targetYStr);
    }
    catch(...)
    {
        instanceId = 0;
        objectId = 0;
        targetX = 0;
        targetY = 0;
    }
    if(instanceId == 0 || objectId == 0) return commandResult;
    
    CWorld* world = CWorld::getInstance();
    CSetPathTargetRequestParam gameRequestParams(instanceId, objectId, CCellCoords(targetX, targetY));
    CGameRequest  gameRequest(user, gameRequestParams, now);
    CGameResponce responce(std::move(world->getRequestHandler().executeRequest(gameRequest)));
    
    std::vector<uint8_t>* resultBinData = new std::vector<uint8_t>(std::move(responce.getBinData()));
    
    commandResult.setIsSuccess(true);
    commandResult.setBinData(resultBinData);
    commandResult.setType(CCommandResult::CR_BIN);
    commandResult.appendHeader("Access-Control-Allow-Origin: *");
    return commandResult;
}

CCommandResult CSummonMasterCommandManager::gameGetInstancesList(CFCGIRequest* currRequest) const
{
	CCommandResult commandResult;
    commandResult.setData("");
    time_t now;
    time(&now);
    
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
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
    commandResult.setData("");
    time_t now;
    time(&now);
       
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
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
    commandResult.setData("");
    time_t now;
    time(&now);
    
    if(!identAndCheckUser(currRequest) || isUserAccessClosed(currRequest) ) return commandResult;
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
	commandResult.setData("");

	std::string login = request->post.get("login", "");
	std::string pass  = request->post.get("pass", "");
	std::string newUserStr = request->post.get("newuser", "false");
	bool isNewUser = newUserStr == "true" ? 1 : 0;
    
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
    const CDefaultUser* user = currRequest->getUser();
   
    json result = json::object();
    result["cookie"] = user->getCookie();
    result["id"]  = user->getUserId();
    
	commandResult.setIsSuccess(true);
	commandResult.setData(result.dump());
    commandResult.appendHeader("Access-Control-Allow-Credentials:false");
    commandResult.appendHeader("Access-Control-Allow-Origin:http://summonmaster.com");
   // commandResult.appendHeader("Access-Control-Allow-Headers : Origin, X-Requested-With, Content-Type, Accept, X-OurCustomHeader");
   
	return commandResult;
}

CCommandResult CSummonMasterCommandManager::logoutCommand(CFCGIRequest* currRequest) const
{
	CCommandResult commandResult;
	commandResult.setData("");
	
	CSessionManager* sessionManager = CManagers::getInstance()->getSessionManager();
	sessionManager->logoutUser(currRequest);
    const CDefaultUser* user = currRequest->getUser();
    
    json result = json::object();
    result["cookie"] = user->getCookie();
    result["id"] = user->getUserId();

	commandResult.setIsSuccess(true);
	commandResult.setData(result.dump());
    commandResult.appendHeader("Access-Control-Allow-Origin: http://summonmaster.com");
    commandResult.appendHeader("Access-Control-Allow-Credentials:false");
	return commandResult;
}


bool CSummonMasterCommandManager::identAndCheckUser(CFCGIRequest* currRequest) const
{
    CFCGIRequestHandler* request = currRequest->getRequestForModify();
    std::string userIdStr       = request->post.get("user_id", "");
    std::string userSessionKey  = request->post.get("user_session", "");
        
    unsigned int userId = 0;
    try
    {
        userId = std::stoi(userIdStr);
    }
    catch(...)
    {
        userId = 0;
    }
    if(userId == 0 || userSessionKey.length() < 4) return false;
    
    CSummonMasterUser* newUser = new CSummonMasterUser(userId);
    if(!newUser) return false;
    newUser->fillUserDataById(userId);
    if(newUser->getIsValid() && newUser->getCookie() == userSessionKey)
    {
        currRequest->setUser(newUser);
        return true;
    }
    else
    {
        delete newUser;
    }
    return false;
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
