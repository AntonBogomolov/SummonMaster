#include "CSummonMasterUser.h"

#include "novemberlib/utils/utils.h"
#include "novemberlib/managers/CManagers.h"
#include "novemberlib/managers/CDBManager.h"
#include "novemberlib/utils/CLog.h"

#include "novemberlib/HTTPClient/IResultsStore.h"

CSummonMasterUser::CSummonMasterUser()
{
    isTasksInit = false;
}

CSummonMasterUser::CSummonMasterUser(int userId) : CDefaultUser(userId)
{
    isTasksInit = false;
}

CSummonMasterUser::~CSummonMasterUser()
{
    for(auto it = tasks.begin(); it != tasks.end(); ++it)
    {
        delete (*it);
    }
}

const std::string& CSummonMasterUser::getCharacterKey() const
{
    return characterKey;
}

void CSummonMasterUser::setCharacterKey(const std::string& key)
{
    CLog::getInstance()->addInfo("update char key");
    if(getIsUserGuest() || getIsAccessClosed()) return;
    
    CDBManager* dbManager = CManagers::getInstance()->getDBManager();
	shared_ptr<CDBRequest> dbRequest(dbManager->createDBRequest());
    dbRequest->updateRequest("Users", "`charKey` = '" + dbManager->getEscapeString(key) +"'", "`id` = " + valueToString(userId));    
}

void CSummonMasterUser::afterFillUserData()
{
	CDBManager* dbManager = CManagers::getInstance()->getDBManager();
	std::shared_ptr<CDBRequest> dbRequest(dbManager->createDBRequest());
    
    if(getIsUserGuest() || getIsAccessClosed()) return;
    
    const CDBRequestResult* reqResult = dbRequest->selectRequest(CDBValues("tasks,premEndDate,charKey"), "Users", "`id`="+valueToString(userId), " LIMIT 1");
    if(dbRequest->getIsLastQuerySuccess() && reqResult != NULL && reqResult->getRowsCnt() > 0)
    {
        taskHashsStr = reqResult->getStringValue(0, 0);
        premEndDate  = reqResult->getLongValue(0, 1);
        characterKey = reqResult->getStringValue(0,2);
    }   
    split(taskHashs, taskHashsStr, ",");   
	setIsValid(true);
}

const vector<string> CSummonMasterUser::getTaskHashs() const
{
    return taskHashs;
}

void CSummonMasterUser::addTaskHash(const string taskHash)
{
    bool isTaskExsits = false;
    for(auto it = taskHashs.begin(); it != taskHashs.end(); ++it)
    {
        if(*it == taskHash) 
        {
            isTaskExsits = true;
            break;
        }
    }
    if(isTaskExsits)
    {
        taskHashs.push_back(taskHash);
        updateTaskHashsInDB();
    }
}
void CSummonMasterUser::removeTaskHash(const string taskHash)
{
    for(auto it = taskHashs.begin(); it != taskHashs.end(); ++it)
    {
        if(*it == taskHash) 
        {
            taskHashs.erase(it);
            updateTaskHashsInDB();
            return;
        }
    }
}
void CSummonMasterUser::removeAllTaskHashs()
{
    taskHashs.clear();
    updateTaskHashsInDB();
}
        
void CSummonMasterUser::updateTaskHashsInDB()
{
    CLog::getInstance()->addInfo("updateTaskHashsInDB");
    if(getIsUserGuest() || getIsAccessClosed()) return;
    
    string hashsForDB = "";
    for(size_t i = 0; i < taskHashs.size(); i++)
    {
        hashsForDB += taskHashs[i];
        if(i != taskHashs.size() - 1) hashsForDB += ",";
    }
    CLog::getInstance()->addInfo(hashsForDB);
    CDBManager* dbManager = CManagers::getInstance()->getDBManager();
	shared_ptr<CDBRequest> dbRequest(dbManager->createDBRequest());
    dbRequest->updateRequest("Users", "`tasks` = '" + hashsForDB+"'", "`id` = " + valueToString(userId));    
}

bool CSummonMasterUser::getIsPrem() const
{
    if(premEndDate == 1) return true;
    
    time_t now;
    time(&now);
    
    if(premEndDate < now) return false;
    return true;
}

time_t CSummonMasterUser::getPremEndDate() const
{
    return premEndDate;
}

time_t CSummonMasterUser::getPremTimeLeft() const
{
    if(premEndDate == 1) return 99999;    
    time_t now;
    time(&now);
    
    if(premEndDate < now) return 0;
    return premEndDate - now;
}
               
void CSummonMasterUser::initTasks()
{
    for(size_t i = 0; i < taskHashs.size(); i++)
    {
        CResult* result =  CResult::loadFromDB(taskHashs[i]);
        if(result) tasks.push_back(result);        
    }
    isTasksInit = true;
}

const vector<CResult*> CSummonMasterUser::getTasks()
{    
    if(!isTasksInit) initTasks();
    return tasks;
}
