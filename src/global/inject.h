#ifndef GLOBAL_INJECT_H
#define GLOBAL_INJECT_H

#define STATIC_GETTER(getterName, Cls) \
static Cls* getterName() \
{ \
    static Cls i; \
    return &i; \
}

#endif // GLOBAL_INJECT_H
