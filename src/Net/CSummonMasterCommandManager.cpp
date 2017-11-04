#include "CSummonMasterCommandManager.h"

#include "novemberlib/novemberlib.h"
#include "CSummonMasterUser.h"

#include "novemberlib/HTTPClient/CHTTPClient.h"
#include "novemberlib/utils/json.h"
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

    if (command == "login")             return loginCommand(currRequest);
    if (command == "logout")            return logoutCommand(currRequest);

    result.setIsValid(false);
    return result;
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
