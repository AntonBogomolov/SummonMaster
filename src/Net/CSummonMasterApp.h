#ifndef CVKGETAPP_H
#define CVKGETAPP_H

#include "novemberlib/FCGI/CFCGIApp.h"


class CSummonMasterApp : public CFCGIApp
{
	public:
		CSummonMasterApp();
		virtual ~CSummonMasterApp();
	protected:
		virtual void init();
	private:
		void initDB();
};

#endif // CVKGETAPP_H
