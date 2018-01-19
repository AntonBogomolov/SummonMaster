#include "csuccesspage.h"

CSuccessPage::CSuccessPage(const std::string name, const CFCGIRequest* currRequest) : CSitePage(name, currRequest)
{
    //ctor
}

CSuccessPage::~CSuccessPage()
{
    //dtor
}

std::string CSuccessPage::buildContent() const
{
	CTemplateHelper* templateManager = CTemplateHelper::getInstance();
	std::map<std::string, std::string> params;
	std::string tmpStr;

	const CHTMLTemplate* contentTemplate = templateManager->findTemplate("content");
	const CHTMLTemplate* contactTemplate = templateManager->findTemplate("successPage");
	if (contentTemplate == NULL || contactTemplate == NULL) return "Missing template";

	std::string contactTemplateReadyContent = contactTemplate->getHTMLData();
	params.clear();

	//params["{NAV}"] = buildNavBar(currRequest->getUser());
	//params["{LEFT}"] = buildLeftPanel();
	params["{CONTENT}"] = contactTemplateReadyContent;

	return contentTemplate->getHTMLData(&params);
}
