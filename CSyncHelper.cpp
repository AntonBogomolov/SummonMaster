#include "CSyncHelper.h"

CSyncHelper::CSyncHelper()
{
	mtxResource = new std::mutex();
	mtxLog 		= new std::mutex();
	mtxFile		= new std::mutex();
	mtxDB		= new std::mutex();
	mtxMessage	= new std::mutex();
	mtxDraw 	= new std::mutex();
}

CSyncHelper::~CSyncHelper()
{
	delete mtxLog;
	delete mtxFile;
	delete mtxResource;
	delete mtxDB;
	delete mtxMessage;
	delete mtxDraw;
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

std::mutex* CSyncHelper::getDrawMutex() const
{
	return mtxDraw;
}
