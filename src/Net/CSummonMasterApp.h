#ifndef CVKGETAPP_H
#define CVKGETAPP_H

#include "novemberlib/FCGI/CFCGIApp.h"
#include <thread>

class CSummonMasterApp : public CFCGIApp
{
	public:
		CSummonMasterApp();
		virtual ~CSummonMasterApp();
	protected:
		virtual void init();
	private:
		void initDB();
        
        std::thread* gameThread;
};

#endif // CVKGETAPP_H
