#ifndef IWANY_H
#define IWANY_H

#include <any>
#include <iostream>

namespace iw {
class Any
{
public:
    Any() = default;
    Any(std::any data);

    template<typename T> T get() const
    {
        return std::any_cast<T>(m_data);
    }
private:
    std::any m_data;
};
}

#endif // IWANY_H
