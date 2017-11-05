#ifndef CSYNCHELPER_H
#define CSYNCHELPER_H

#include "novemberlib/interfaces/ITemplateSingleton.h"

#include <mutex>
#include <chrono>
#include <thread>
#include <shared_mutex>

class CSyncHelper : public ITemplateSingleton<CSyncHelper>
{
	public:
		std::mutex* getLogMutex() const;
		std::mutex* getResourceMutex() const;
		std::mutex* getFileMutex() const;
		std::mutex* getDBMutex() const;
		std::mutex* getMessageMutex() const;
		std::shared_timed_mutex* getInstanceMutex() const;

		virtual ~CSyncHelper();
	protected:
	private:
		std::mutex* mtxLog;
		std::mutex* mtxFile;
		std::mutex* mtxResource;
		std::mutex* mtxDB;
		std::mutex* mtxMessage;
		std::shared_timed_mutex* mtxInstance;

		friend CSyncHelper* ITemplateSingleton::getInstance();
		CSyncHelper();
};

#endif // CSYNCHELPER_H
