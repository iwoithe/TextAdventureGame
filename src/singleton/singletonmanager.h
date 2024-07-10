#ifndef SINGLETON_SINGLETONMANAGER_H
#define SINGLETON_SINGLETONMANAGER_H

#include <functional>
#include <vector>

#include "iwany.h"

#include "audio/audioengine.h"
#include "dispatcher/dispatcher.h"

using namespace iw;

#define INJECT_SINGLETON_ALIAS(aliasName, clsGetterFunc, Cls)\
private:\
    Cls* aliasName()\
    {\
        return SingletonManager::instance()->clsGetterFunc();\
    }

class SingletonManager
{
public:
    SingletonManager();
    SingletonManager(const SingletonManager& s) = delete;
    ~SingletonManager();

    static SingletonManager* instance();

    AudioEngine* audioEngine();
    Dispatcher* dispatcher();

private:
    static SingletonManager* m_instancePtr;

    AudioEngine* m_audioEngine;
    Dispatcher* m_dispatcher;
};

#endif // SINGLETON_SINGLETONMANAGER_H
