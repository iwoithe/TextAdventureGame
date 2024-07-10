#ifndef DISPATCHER_DISPATCHER_H
#define DISPATCHER_DISPATCHER_H

#include <map>
// Use std::string temporarily until iw::String works with std::map
#include <string>
#include <functional>
#include <vector>

#include "iwany.h"

using namespace iw;


// using Parameters = std::initializer_list<Any>;

class Parameters
{
public:
    Parameters() = default;

    Parameters(std::initializer_list<Any> params)
    {
        for (Any param : params) {
            m_data.push_back(param);
        }
    }

    const Any& operator[](const size_t& index) const
    {
        return get(index);
    }

    const Any& get(int index) const
    {
        return m_data[index];
    }
private:
    std::vector<Any> m_data;
};


using Action = std::function<void(Parameters)>;

class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher();

    Dispatcher(const Dispatcher& obj) = delete;

    void dispatch(const std::string& code, Parameters p);

    void reg(const std::string& code, Action action);
private:
    std::map<std::string, Action> m_actionsMap;
};

#endif // DISPATCHER_DISPATCHER_H
