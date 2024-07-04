#ifndef IWVARIANT_H
#define IWVARIANT_H

#include <any>
#include <variant>

#include "iwstring.h"

namespace iw {
using VariantType = std::variant<String, int, char>;

class Variant
{
public:
    Variant() = default;
    Variant(VariantType type);

    template<typename T> const T& get()
    {
        return std::get<T>(m_data);
    }
private:
    VariantType m_data;
};
}

#endif // IWVARIANT_H
