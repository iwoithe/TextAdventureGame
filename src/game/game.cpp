#include "game.h"

#include <conio.h>
#include <cstdlib>
#include <time.h>

#include "async/processevents.h"

#include "global/delete.h"
#include "dispatcher/dispatcher.h"
#include "global/log.h"

#include "items/items.h"
#include "player/player.h"

Game::Game()
{
    srand(time(0));

    initGameObjects();

    m_isRunning = false;
    m_rooms = {};
    addRoom("Lobby", nullptr, RoomPos(0, 0));
    m_currentRoom = room(RoomPos(0, 0));

    setMenu(Menu::Main);

    m_currentMenuChanged.onReceive(nullptr, [](Menu menu) {
        switch (menu) {
            case Menu::Main:
                String("Main").writeToConsole();
                break;
            case Menu::MoveRoom:
                String("Move Room").writeToConsole();
                break;
            case Menu::Inventory:
                String("Inventory").writeToConsole();
                break;
            case Menu::Spellbook:
                String("Spellbook").writeToConsole();
                break;
            default:
                break;
        }
    });
}

Game::~Game()
{
    for (IGameObject* gameObject : m_gameObjects) {
        gameObject->deInit();
    }

    DEL_PTR_S(m_currentRoom);
    DEL_STD_VEC(m_gameObjects);
    DEL_STD_VEC(m_rooms);
}

void Game::addGameObject(IGameObject* gameObject)
{
    m_gameObjects.push_back(gameObject);
}

void Game::initGameObjects()
{
    addGameObject(new Player());

    for (IGameObject* gameObject : m_gameObjects) {
        gameObject->init();
    }
}

void Game::addRoom(Room* r)
{
    m_rooms.push_back(r);
}

void Game::addRoom(const String& description, IItem* item, const RoomPos& roomPos)
{
    dispatcher()->dispatch("player-add-item-to-inventory", Parameters({ Any(item) }));

    Room* r = new Room(description, item, roomPos);
    m_rooms.push_back(r);
}

void Game::addRandomRoom(const RoomPos& roomPos)
{
    addRoom("Hello", getRandomItem(), roomPos);
}

Room* Game::room(const RoomPos& roomPos)
{
    // Get the room at position roomPos
    for (Room* r : m_rooms) {
        if (r->roomPos().x == roomPos.x && r->roomPos().y == roomPos.y) {
            return r;
        }
    }

    return nullptr;
}

Menu Game::currentMenu() const
{
    return m_currentMenu;
}

async::Channel<Menu> Game::currentMenuChanged()
{
    return m_currentMenuChanged;
}

void Game::setMenu(Menu menu)
{
    if (menu == m_currentMenu) {
        return;
    }

    m_currentMenu = menu;
    m_currentMenuChanged.send(menu);
}

void Game::handleInput()
{
    if (kbhit()) {
        int key = getch();
        handleQuit(key);

        switch (m_currentMenu) {
            case Menu::Main:
                mainMenu(key);
                break;
            case Menu::MoveRoom:
                moveRoomMenu(key);
                break;
            case Menu::Inventory:
                break;
            case Menu::Spellbook:
                break;
        }
    }
}

void Game::handleQuit(const int& key)
{
    if (key == KEY_ESCAPE) {
        switch (m_currentMenu) {
            case Menu::Main:
                m_isRunning = false;
                break;
            case Menu::MoveRoom:
            case Menu::Inventory:
            case Menu::Spellbook:
                setMenu(Menu::Main);
                break;
        }
    }
}

void Game::mainMenu(const int& key)
{
    switch (key) {
        case KEY_m:
            setMenu(Menu::MoveRoom);
            break;
        case KEY_i:
            setMenu(Menu::Inventory);
            break;
        case KEY_s:
            setMenu(Menu::Spellbook);
        default:
            break;
    }
}

void Game::moveRoomMenu(const int& key)
{
    if (key == KEY_ENTER && _m__moveToRoomRel > 0 && _m__moveToRoomRel <= 4) {
        Direction dir;
        switch (_m__moveToRoomRel) {
            case 1:
                dir = Direction::Left;
                addRandomRoom(RoomPos(m_currentRoom->roomPos().x - 1, m_currentRoom->roomPos().y));
                break;
            case 2:
                dir = Direction::Up;
                addRandomRoom(RoomPos(m_currentRoom->roomPos().x, m_currentRoom->roomPos().y + 1));
                break;
            case 3:
                dir = Direction::Right;
                addRandomRoom(RoomPos(m_currentRoom->roomPos().x + 1, m_currentRoom->roomPos().y));
                break;
            case 4:
                dir = Direction::Down;
                addRandomRoom(RoomPos(m_currentRoom->roomPos().x, m_currentRoom->roomPos().y - 1));
                break;
            default:
                dir = Direction::Right;
                addRandomRoom(RoomPos(m_currentRoom->roomPos().x + 1, m_currentRoom->roomPos().y));
                break;
        }

        dispatcher()->dispatch("player-move-room", Parameters({ Any(dir) }));
        setMenu(Menu::Main);
    }

    switch (key) {
        case KEY_1:
            _m__moveToRoomRel = 1;
            break;
        case KEY_2:
            _m__moveToRoomRel = 2;
            break;
        case KEY_3:
            _m__moveToRoomRel = 3;
            break;
        case KEY_4:
            _m__moveToRoomRel = 4;
            break;
        default:
            break;
    }
}

bool Game::isRunning() const
{
    return m_isRunning;
}

void Game::run()
{
    m_isRunning = true;

    while (m_isRunning) {
        app::async::processEvents();
        handleInput();
    }
}
