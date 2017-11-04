#include "cindexpage.h"

#include "novemberlib/HTTPClient/CHTTPClient.h"
#include "novemberlib/utils/json.h"

CIndexPage::CIndexPage(const std::string name, const CFCGIRequest* currRequest) : CSitePage(name, currRequest)
{
	//ctor
}

CIndexPage::~CIndexPage()
{
	//dtor
}

std::string CIndexPage::buildContent() const
{
	CTemplateHelper* templateManager = CTemplateHelper::getInstance();
	std::map<std::string, std::string> params;
	std::string tmpStr;

	const CHTMLTemplate* contentTemplate = templateManager->findTemplate("content");
	const CHTMLTemplate* indexTemplate   = templateManager->findTemplate("indexPage");
	const CHTMLTemplate* loginTemplate   = templateManager->findTemplate("loginForm");
	if (contentTemplate == NULL || indexTemplate == NULL) return "Missing template";
    int userId = currRequest->getUser()->getUserId();

	std::string indexTemplateReadyContent = indexTemplate->getHTMLData(&params);
	params.clear();

    //params["{LOGINBOX}"] = loginTemplate->getHTMLData();
	params["{RETURNPAGE}"] = "index";
	params["{USERID}"] = valueToString(userId);
	//params["{NAV}"] = buildNavBar(currRequest->getUser());
	params["{LEFT}"] = "";
	params["{CONTENT}"] = indexTemplateReadyContent;

	return contentTemplate->getHTMLData(&params);
}
