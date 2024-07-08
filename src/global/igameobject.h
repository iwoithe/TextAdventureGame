#ifndef GLOBAL_GAMEOBJECT_H
#define GLOBAL_GAMEOBJECT_H

class IGameObject
{
public:
    virtual void init() = 0;
    virtual void deInit() = 0;
};

#endif // GLOBAL_GAMEOBJECT_H
