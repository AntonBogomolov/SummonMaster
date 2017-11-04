#pragma once 

//#include "novemberlib/interfaces/ITemplateSingleton.h"
//#include <thread>
//#include <map>
//#include <queue>

enum class ENEvent {NOTSET, INVALIDATE_MAP_REGION};

class CEventParam
{
public:
    CEventParam(ENEvent type)
    {
        this->eventType = type;
    }
    CEventParam(const CEventParam& param)
    {
        this->eventType = param.getEventType();
    }
    virtual ~CEventParam()
    {
        
    }
    ENEvent getEventType() const
    {
        return eventType;
    }
protected:
    ENEvent eventType;
};

class IEventHandler
{
public:
    IEventHandler()
    {
        
    }    
    virtual ~IEventHandler()
    {
        
    }
    virtual void sendMessage(const IEventHandler& messageAccepter, const CEventParam* eventParams)
    {
        
    }
    virtual void receiveMessage(const IEventHandler& messageSender, const CEventParam* eventParams)
    {
        
    }
protected:

};
/*
class CEvent
{
public:
    CEvent( const CEventHandler& messageAccepter, const CEventHandler& messageSender, const CEventParam* eventParams) :
            messageAccepter(messageAccepter), messageSender(messageSender), eventParams(eventParams)
    {
        
    }
    ~CEvent()
    {
        delete eventParams;
    }
    
    const CEventHandler& messageAccepter;
    const CEventHandler& messageSender;
    const CEventParam* eventParams;
};
*/
/*
class CEventDispatcher : public ITemplateSingleton<CEventDispatcher>
{
public:
    virtual ~CEventDispatcher();
    
    void stop()
    {
        isWorking = false;
    }
    bool getIsWorking() const
    {
        return isWorking;
    }
    void clearEventsQueue();   
    void sendEventTo(CEvent* event);
protected:
private:
    CEventDispatcher();
    void eventLoop();
    
    bool isWorking;
    std::thread worker;
    std::queue<CEvent*> eventQueue;
    std::map<unsigned int, CEventHandler*> eventHandlers;
    friend CEventDispatcher* ITemplateSingleton::getInstance();
};
*/