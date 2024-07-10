#ifndef GAME_H
#define GAME_H

#include "async/asyncable.h"
#include "async/channel.h"
#include "async/notification.h"

#include "audio/audioengine.h"

#include "dispatcher/dispatcher.h"

#include "global/enums.h"
#include "global/igameobject.h"
#include "iwstring.h"
#include "iwany.h"

#include "room/room.h"
#include "singleton/singletonmanager.h"

// TODO: "Special" keys return 224 as well to avoid clashes with other ASCII characters
#define KEY_BACKSPACE '\b'
#define KEY_ENTER 13
#define KEY_ESCAPE 27
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

#define KEY_SP 32

#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

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

enum Menu {
    Main,
    MoveRoom,
    Inventory,
    SpellMenu,
    ListMenu
};

using namespace app;
using namespace iw;

class Game : public async::Asyncable
{
    INJECT_SINGLETON_ALIAS(dispatcher, dispatcher, Dispatcher);
    INJECT_SINGLETON_ALIAS(audioEngine, audioEngine, AudioEngine);
public:
    Game();
    ~Game();

    void init();

    void addGameObject(IGameObject* gameObject);
    void initGameObjects();

    void addRoom(Room* r);
    void addRoom(const String& description, IItem* item, const RoomPos& roomPos);
    void addRandomRoom(const RoomPos& roomPos);
    Room* findRoom(const RoomPos& roomPos);

    Menu currentMenu() const;
    async::Channel<Menu> currentMenuChanged();

    void setMenu(Menu menu);

    void gameIntro() const;
    void displayMenuIntro(Menu menu);
    void displayMoveRoomMenuInstructions() const;
    void displayInventoryInstructions();
    void displaySpellMenuInstructions();
    void displayListMenuInstructions() const;

    void loadAvailableItems();
    void loadAvailableSpells();

    void handleInput();
    void handleQuit(const int& key);
    void handleMainMenu(const int& key);
    void handleMoveRoomMenu(const int& key);
    void handleInventoryMenu(const int& key);
    void handleSpellMenu(const int& key);
    void handleListMenu(const int& key);

    bool isRunning() const;
    void run();

private:
    std::vector<IGameObject*> m_gameObjects;

    Menu m_currentMenu;
    async::Channel<Menu> m_currentMenuChanged;

    bool m_isRunning;
    std::vector<Room*> m_rooms;

    Room* m_currentRoom;

    // Relative room, a value 1 - 4, only to be used in moveRoomMenu()
    int _m__moveToRoomRel;

    // handleInventoryMenu inputted number
    int _m__himNum = 0;
    // handleSpellMenu inputted number
    int _m__hsmNum = 0;
    // handleListMenu inputted string
    String _m__hlmStr = "";

    int m_playerInventorySize;
    int m_playerSpellsSize;

    std::vector<String> m_availableItemsNames;
    std::vector<String> m_availableItemsDescriptions;
    std::vector<String> m_availableSpellsNames;
    std::vector<String> m_availableSpellsDescription;
};

#endif // GAME_H
