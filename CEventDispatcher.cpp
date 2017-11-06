#include "CEventDispatcher.h"

#include "utils.h"

// ==================================================
/*

CEventDispatcher::CEventDispatcher()
{
    isWorking = true;
    worker = std::thread(&CEventDispatcher::eventLoop, this);
    
    worker.join();
}
CEventDispatcher::~CEventDispatcher()
{
    clearEventsQueue();
    stop();
}

void CEventDispatcher::clearEventsQueue()
{
    CSyncHelper::getInstance()->getMessageMutex()->lock();
    while(!eventQueue.empty())
    {
        CEvent* event = eventQueue.front();
        eventQueue.pop();
        delete event;
    }
    CSyncHelper::getInstance()->getMessageMutex()->unlock();
}
void CEventDispatcher::sendEventTo(CEvent* event)
{
    CSyncHelper::getInstance()->getMessageMutex()->lock();
    eventQueue.push(event);
    CSyncHelper::getInstance()->getMessageMutex()->unlock();
}
void CEventDispatcher::eventLoop()
{
    while(isWorking)
    {
        if(eventQueue.empty())
        { 
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            continue;
        }
       
        while(!eventQueue.empty())
        {
            CEvent* event = eventQueue.front();
            eventQueue.pop();
            event->messageAccepter.receiveMessage(event.eventParams)
            
            delete event;
        }
    }
}
*/