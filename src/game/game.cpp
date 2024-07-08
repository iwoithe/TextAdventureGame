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

    init();

    gameIntro();
    setMenu(Menu::Main);
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

void Game::init()
{
    m_currentMenuChanged.onReceive(nullptr, [&](Menu menu) {
        displayMenuIntro(menu);
    });
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

void Game::gameIntro() const
{
    String("Text Adventure Game").writeToConsole();
    String("Made by Ilias Woithe").writeToConsole();
    String().appendColor(Color::Magenta, ColorLayer::Foreground).append("Press [Esc] or [q] to go back a menu/quit if in main menu").writeToConsole();
    String("Press [m] to enter the move menu").writeToConsole();
    String("Press [i] to enter the inventory menu").writeToConsole();
    String("Press [u] to use an item (only works in the inventory menu)").writeToConsole();
    String("Press [s] to enter the spellbook menu").appendColor(Color::Default, ColorLayer::Foreground).writeToConsole();
}

void Game::displayMenuIntro(Menu menu)
{
    // Insert blank line between title text
    String().writeToConsole();

    String menuTitleText;
    menuTitleText.appendColor(Color::Green, ColorLayer::Foreground);
    switch (menu) {
        case Menu::Main:
            menuTitleText.append("[Main Menu]");
            break;
        case Menu::MoveRoom:
            menuTitleText.append("[Move Room Menu]");
            break;
        case Menu::Inventory:
            menuTitleText.append("[Inventory Menu]");
            break;
        case Menu::Spellbook:
            menuTitleText.append("[Spellbook Menu]");
            break;
        default:
            break;
    }

    menuTitleText.appendColor(Color::Default, ColorLayer::Foreground);
    menuTitleText.writeToConsole();

    // Contextual text/instructions
    switch (menu) {
        case Menu::Main:
            dispatcher()->dispatch("player-display-stats", Parameters());
            break;
        case Menu::MoveRoom:
            displayMoveRoomMenuInstructions();
            break;
        case Menu::Inventory:
            displayInventoryInstructions();
            break;
        case Menu::Spellbook:
            break;
        default:
            break;
    }
}

void Game::displayMoveRoomMenuInstructions() const
{
    String infoText;
    infoText.appendColor(Color::Magenta, ColorLayer::Foreground);
    infoText.append("Type 1 - 4 to change the room you want to move to");
    infoText.appendColor(Color::Default, ColorLayer::Foreground);
    infoText.writeToConsole();
    String("Move to room:  ").writeToConsole(false);
}

void Game::displayInventoryInstructions()
{
    String infoText;
    infoText.appendColor(Color::Magenta, ColorLayer::Foreground);
    infoText.append("Press [Esc] to return to ");
    infoText.appendColor(Color::Green, ColorLayer::Foreground);
    infoText.append("[Main Menu]");
    infoText.appendColor(Color::Magenta, ColorLayer::Foreground);
    infoText.append(", [u] to open the ");
    infoText.appendColor(Color::Green, ColorLayer::Foreground);
    infoText.append("[Use Item Menu]");
    infoText.appendColor(Color::Default, ColorLayer::Foreground);
    infoText.writeToConsole();
    dispatcher()->dispatch("player-display-inventory", Parameters());
}

void Game::handleInput()
{
    if (kbhit()) {
        int key = getch();
        handleQuit(key);

        switch (m_currentMenu) {
            case Menu::Main:
                handleMainMenu(key);
                break;
            case Menu::MoveRoom:
                handleMoveRoomMenu(key);
                break;
            case Menu::Inventory:
                handleInventoryMenu(key);
                break;
            case Menu::Spellbook:
                break;
        }
    }
}

void Game::handleQuit(const int& key)
{
    if (key == KEY_ESCAPE || key == KEY_q) {
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

void Game::handleMainMenu(const int& key)
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

void Game::handleMoveRoomMenu(const int& key)
{
    if (key == KEY_ENTER && _m__moveToRoomRel > 0 && _m__moveToRoomRel <= 4) {
        Direction dir;
        RoomPos newPos;
        switch (_m__moveToRoomRel) {
            case 1:
                dir = Direction::Left;
                newPos = RoomPos(m_currentRoom->roomPos().x - 1, m_currentRoom->roomPos().y);
                break;
            case 2:
                dir = Direction::Up;
                newPos = RoomPos(m_currentRoom->roomPos().x, m_currentRoom->roomPos().y + 1);
                break;
            case 3:
                dir = Direction::Right;
                newPos = RoomPos(m_currentRoom->roomPos().x + 1, m_currentRoom->roomPos().y);
                break;
            case 4:
                dir = Direction::Down;
                newPos = RoomPos(m_currentRoom->roomPos().x, m_currentRoom->roomPos().y - 1);
                break;
            default:
                dir = Direction::Right;
                newPos = RoomPos(m_currentRoom->roomPos().x + 1, m_currentRoom->roomPos().y);
                break;
        }

        addRandomRoom(newPos);
        m_currentRoom = room(newPos);

        dispatcher()->dispatch("player-move-room", Parameters({ Any(dir) }));
        // Flush and end the current line
        String().writeToConsole();
        setMenu(Menu::Main);
    }

    switch (key) {
        case KEY_1:
            _m__moveToRoomRel = 1;
            goto finally;
        case KEY_2:
            _m__moveToRoomRel = 2;
            goto finally;
        case KEY_3:
            _m__moveToRoomRel = 3;
            goto finally;
        case KEY_4:
            _m__moveToRoomRel = 4;
            goto finally;
        finally:
            String().append("\033[1D").append(_m__moveToRoomRel).writeToConsole(false);
            break;
        default:
            break;
    }
}

void Game::handleInventoryMenu(const int& key)
{
    switch (key) {
        case KEY_u:
            // switch to item selection menu
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
