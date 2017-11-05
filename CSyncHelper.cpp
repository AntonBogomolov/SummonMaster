#include "CSyncHelper.h"

CSyncHelper::CSyncHelper()
{
	mtxResource = new std::mutex();
	mtxLog 		= new std::mutex();
	mtxFile		= new std::mutex();
	mtxDB		= new std::mutex();
	mtxMessage	= new std::mutex();
	mtxInstance	= new std::shared_timed_mutex();
}

CSyncHelper::~CSyncHelper()
{
	delete mtxLog;
	delete mtxFile;
	delete mtxResource;
	delete mtxDB;
	delete mtxMessage;
	delete mtxInstance;
}

std::mutex* CSyncHelper::getLogMutex() const
{
	return mtxLog;
}

std::mutex* CSyncHelper::getResourceMutex() const
{
	return mtxResource;
}

std::mutex* CSyncHelper::getFileMutex() const
{
	return mtxFile;
}

std::mutex* CSyncHelper::getDBMutex() const
{
	return mtxDB;
}

std::mutex* CSyncHelper::getMessageMutex() const
{
	return mtxMessage;
}

std::shared_timed_mutex* CSyncHelper::getInstanceMutex() const
{
	return mtxInstance;
}
