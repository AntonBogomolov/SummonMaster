#ifndef CSYNCHELPER_H
#define CSYNCHELPER_H

#include "novemberlib/interfaces/ITemplateSingleton.h"

#include <mutex>
#include <chrono>
#include <thread>

class CSyncHelper : public ITemplateSingleton<CSyncHelper>
{
	public:
		std::mutex* getLogMutex() const;
		std::mutex* getResourceMutex() const;
		std::mutex* getFileMutex() const;
		std::mutex* getDBMutex() const;
		std::mutex* getMessageMutex() const;
		std::mutex* getDrawMutex() const;

		virtual ~CSyncHelper();
	protected:
	private:
		std::mutex* mtxLog;
		std::mutex* mtxFile;
		std::mutex* mtxResource;
		std::mutex* mtxDB;
		std::mutex* mtxMessage;
		std::mutex* mtxDraw;

		friend CSyncHelper* ITemplateSingleton::getInstance();
		CSyncHelper();
};

#endif // CSYNCHELPER_H
