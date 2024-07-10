#include "singletonmanager.h"

#include <stdexcept>

#include "global/delete.h"

SingletonManager::SingletonManager()
{
    m_audioEngine = new AudioEngine();
    m_dispatcher = new Dispatcher();
    m_instancePtr = nullptr;
}

SingletonManager::~SingletonManager()
{
    DEL_PTR_S(m_audioEngine);
    DEL_PTR_S(m_dispatcher);
}

SingletonManager* SingletonManager::m_instancePtr = nullptr;

SingletonManager* SingletonManager::instance()
{
    if (m_instancePtr == nullptr) {
        m_instancePtr = new SingletonManager();
    }

    return m_instancePtr;
}

AudioEngine* SingletonManager::audioEngine()
{
    if (m_audioEngine == nullptr) {
        throw std::runtime_error("[CRITICAL ERROR] m_audioEngine is nullptr");
    }

    return m_audioEngine;
}

Dispatcher* SingletonManager::dispatcher()
{
    if (m_dispatcher == nullptr) {
        throw std::runtime_error("[CRITICAL ERROR] m_dispatcher is nullptr");
    }

    return m_dispatcher;
}
