#include "game/game.h"

#include "global/delete.h"
#include "singleton/singletonmanager.h"


int main()
{
    SingletonManager* sm = new SingletonManager();

    Game game;
    game.run();

    DEL_PTR_S(sm);

    return 0;
}
