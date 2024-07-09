#ifndef SPELLS_ISPELL_H
#define SPELLS_ISPELL_H

#include "iwstring.h"

using namespace iw;

class ISpell
{
public:
    bool operator==(const ISpell& s)
    {
        return m_name == s.name();
    }

    bool operator<(const ISpell& s)
    {
        return m_name < s.name();
    }

    bool operator>(const ISpell& s)
    {
        return m_name > s.name();
    }

    const String& name() const { return m_name; }
    const String& description() const { return m_description; }
    virtual void cast() = 0;
protected:
    String m_name;
    String m_description;
};

bool operator==(const ISpell& i, const String& s);
bool operator<(const ISpell& i, const String& s);
bool operator>(const ISpell& i, const String& s);

bool operator==(const ISpell* i, const String& s);
bool operator<(const ISpell* i, const String& s);
bool operator>(const ISpell* i, const String& s);

#endif //SPELLS_ISPELL_H
