#include "dispatcher.h"

#include "global/log.h"

void Dispatcher::dispatch(const std::string& code, Parameters p)
{
    for (auto& actionMap : m_actionsMap) {
        std::string actionCode = actionMap.first;
        Action action = actionMap.second;

        if (actionCode == code) {
            action(p);
            return;
        }
    }
}

void Dispatcher::reg(const std::string& code, Action action)
{
    m_actionsMap[code] = action;
}
