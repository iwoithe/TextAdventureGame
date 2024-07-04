#ifndef GAME_H
#define GAME_H

#include "async/channel.h"
#include "async/notification.h"

#include "global/inject.h"
#include "iwstring.h"
#include "iwany.h"

#include "room/room.h"

// TODO: "Special" keys return 224 as well to avoid clashes with other ASCII characters
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

#define KEY_SP 32

#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90

#define KEY_a 97
#define KEY_b 98
#define KEY_c 99
#define KEY_d 100
#define KEY_e 101
#define KEY_f 102
#define KEY_g 103
#define KEY_h 104
#define KEY_i 105
#define KEY_j 106
#define KEY_k 107
#define KEY_l 108
#define KEY_m 109
#define KEY_n 110
#define KEY_o 111
#define KEY_p 112
#define KEY_q 113
#define KEY_r 114
#define KEY_s 115
#define KEY_t 116
#define KEY_u 117
#define KEY_v 118
#define KEY_w 119
#define KEY_x 120
#define KEY_y 121
#define KEY_z 122

enum InputMode {
    None,
    Str,
    Character
};

enum Menu {
    Main,
    MoveRoom,
    Inventory,
    Spellbook
};

using namespace app;
using namespace iw;

class Game
{
public:
    Game();
    ~Game();

    void addRoom(Room* room);
    void addRoom(const String& description, IItem* item, const RoomPos& roomPos);

    Menu currentMenu() const;
    async::Channel<Menu> currentMenuChanged();

    Any getInput(InputMode inputMode);
    Any getInput(InputMode inputMode, bool print);
    void handleInput();

    bool isRunning() const;
    void run();

private:
    Menu m_currentMenu;
    async::Channel<Menu> m_currentMenuChanged;

    bool m_isRunning;
    std::vector<Room*> m_rooms;
};

STATIC_GETTER(game, Game)

#endif // GAME_H
