#ifndef CINDEXPAGE_H
#define CINDEXPAGE_H

#include "csitepage.h"

class CIndexPage : public CSitePage
{
    public:
		CIndexPage(const std::string name, const CFCGIRequest* currRequest);
		virtual ~CIndexPage();
	protected:
		virtual std::string buildContent() const;
	private:
};

#endif // CINDEXPAGE_H
