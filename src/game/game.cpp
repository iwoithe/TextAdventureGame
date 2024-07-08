#include "game.h"

#include <conio.h>

#include "async/processevents.h"

#include "global/delete.h"
#include "dispatcher/dispatcher.h"
#include "global/log.h"

#include "player/player.h"

Game::Game()
{
    initGameObjects();

    m_currentMenu = Menu::Main;
    m_isRunning = false;
    m_rooms = {};
    addRoom("Lobby", nullptr, RoomPos(0, 0));
    m_currentRoom = room(RoomPos(0, 0));

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
    delete m_currentRoom;
    for (IGameObject* gameObject : m_gameObjects) {
        gameObject->deInit();
    }

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
    Room* r = new Room(description, item, roomPos);
    m_rooms.push_back(r);
}

void Game::addRandomRoom(const RoomPos& roomPos)
{
    addRoom("Hello", nullptr, roomPos);
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

Any Game::getInput(InputMode inputMode)
{
    return getInput(inputMode, true);
}

Any Game::getInput(InputMode inputMode, bool print)
{
    switch (inputMode) {
        case InputMode::None:
            return Any(String(""));
        case InputMode::Str:
            return Any(String(""));
        case InputMode::Character:
            if (print) {
                String("Enter a character:  ").writeToConsole(false);
            }

            int keyboardCode = 0;

            while (keyboardCode != KEY_ENTER) {
                keyboardCode = getch();
            }

            return Any(keyboardCode);
    }

    return Any();
}

void Game::handleInput()
{
    if (kbhit()) {
        int key = getch();
        if (key == KEY_ESCAPE) {
            switch (m_currentMenu) {
                case Menu::Main:
                    m_isRunning = false;
                    break;
                case Menu::MoveRoom:
                case Menu::Inventory:
                case Menu::Spellbook:
                    m_currentMenu = Menu::Main;
                    m_currentMenuChanged.send(m_currentMenu);
                    break;
            }
        }

        switch (m_currentMenu) {
            case Menu::Main:
                switch (key) {
                    case KEY_m:
                        m_currentMenu = Menu::MoveRoom;
                        m_currentMenuChanged.send(m_currentMenu);
                        break;
                    case KEY_i:
                        m_currentMenu = Menu::Inventory;
                        m_currentMenuChanged.send(m_currentMenu);
                    case KEY_s:
                        m_currentMenu = Menu::Spellbook;
                        m_currentMenuChanged.send(m_currentMenu);
                    default:
                        break;
                }
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

        m_playerMoveRoomRequested.send(dir);
        dispatcher()->dispatch("player-move-room", Parameters({ Any(dir) }));
        m_currentMenu = Menu::Main;

        m_currentMenuChanged.send(m_currentMenu);
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

async::Channel<Direction> Game::playerMoveRoomRequested()
{
    return m_playerMoveRoomRequested;
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
