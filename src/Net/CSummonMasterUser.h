#ifndef CVKGetUser_H
#define CVKGetUser_H

#include "novemberlib/CDefaultUser.h"
#include <vector>

using namespace std;

class CResult;
class CSummonMasterUser : public CDefaultUser
{
	public:
		virtual void afterFillUserData();
        
        const vector<string> getTaskHashs() const;
        const vector<CResult*> getTasks();
        void addTaskHash(const string taskHash);
        void removeTaskHash(const string taskHash);
        void removeAllTaskHashs();
        
        bool getIsPrem() const;
        time_t getPremEndDate() const;
        time_t getPremTimeLeft() const;

		CSummonMasterUser();
		CSummonMasterUser(int userId);
		virtual ~CSummonMasterUser();
	protected:
        vector<string> taskHashs;
        vector<CResult*> tasks;
        string taskHashsStr;
        time_t premEndDate;
        bool isTasksInit;
                
        void initTasks();
        void updateTaskHashsInDB();
	private:

};

#endif // CVKGetUser_H
