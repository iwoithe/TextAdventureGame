#include "ispell.h"

// This is a little janky having a cpp file and kinda breaks what
// interface classes are, but oh well

bool operator==(const ISpell& i, const String& s)
{
    return i.name() == s;
}

bool operator<(const ISpell& i, const String& s)
{
    return i.name() < s;
}

bool operator>(const ISpell& i, const String& s)
{
    return i.name() > s;
}

bool operator==(const ISpell* i, const String& s)
{
    return i->name() == s;
}

bool operator<(const ISpell* i, const String& s)
{
    return i->name() < s;
}

bool operator>(const ISpell* i, const String& s)
{
    return i->name() > s;
}
