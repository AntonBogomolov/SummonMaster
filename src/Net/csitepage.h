#ifndef CSITEPAGE_H
#define CSITEPAGE_H

#include "novemberlib/novemberlib.h"
#include "novemberlib/utils/json.h"
using nlohmann::json;

class CSummonMasterUser;

class CSitePage : public CPage
{
	public:

		CSitePage(const std::string name, const CFCGIRequest* currRequest);
		virtual ~CSitePage();
	protected:
	private:
};

#endif // CSITEPAGE_H
