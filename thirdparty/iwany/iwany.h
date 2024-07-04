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

    template<typename T> T get_s() const
    {
        try {
            return std::any_cast<T>(m_data);
        } catch (const std::bad_any_cast& e) {
            std::cout << e.what() << "\n[WARNING] Returning default constructor value instead" << std::endl;
            T t;
            return t;
        }
    }
private:
    std::any m_data;
};
}

#endif // IWANY_H
