#ifndef CSUCCESSPAGE_H
#define CSUCCESSPAGE_H

#include "csitepage.h"


class CSuccessPage : public CSitePage
{
    public:
        CSuccessPage(const std::string name, const CFCGIRequest* currRequest);
        virtual ~CSuccessPage();
    protected:
        virtual std::string buildContent() const;
    private:
};

#endif // CSUCCESSPAGE_H
