#include "CWorld.h" 

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>

#include <novemberlib/helpers/CConfigHelper.h>
#include <novemberlib/utils/CLog.h>

CWorld::CWorld()
{
    isInit = false;
}

CWorld::~CWorld()
{
    
}

void CWorld::init()
{
    CMapGenerateParams mapGenParams;
    CMapCreationParams globalMapParam(1000, 1200, mapGenParams);
    CInstanceCreationParams instanceCreationParam(globalMapParam, "global map", true);
    
    instanceManager.addInstance(spawner.createInstance<CInstance>(instanceCreationParam));
    
    isInit = true;
}

void CWorld::run()
{
    if(isInit) return;
    
    init();    
    std::thread logicLoopHandler = std::thread(&CWorld::logicLoop, this);
    std::thread watchHandler     = std::thread(&CWorld::watchHandler, this);
    
    watchHandler.join();
    logicLoopHandler.join();
}

void CWorld::collectGarbage()
{
    instanceManager.clearGarbage();
    CLog::getInstance()->addInfo("Garbage  Collected");
}

void CWorld::watchHandler()
{
    CConfigHelper* gs = CConfigHelper::getInstance();
    int garbageCollectTime =  gs->getIntParamValue("garbageCollectTime", 60);

    time_t garbageCollectTimer = 0;
    while(true)
	{
        time_t now;
        time(&now);
        if(now - garbageCollectTimer > garbageCollectTime)
        {
            collectGarbage();
            garbageCollectTimer = now;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void CWorld::logicLoop()
{
    typedef std::chrono::high_resolution_clock clock;
    auto t1 = clock::now();
    auto t2 = clock::now();

    CConfigHelper* gs = CConfigHelper::getInstance();
    int maxLogicFPS =  gs->getIntParamValue("logicFPS", 60);
    while(true)
    {
        t2 = clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        int msCnt = dur.count();
        
        int sleepMSCnt = 0;
        int minMSPerFrame = 1000 / maxLogicFPS;
        if(msCnt < minMSPerFrame) 
        {
            sleepMSCnt = minMSPerFrame - msCnt;
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepMSCnt));
            msCnt = minMSPerFrame;
        }
        float dt = msCnt / 1000.0f;
       
        instanceManager.update(dt);
        t1 = t2;
    }
}
