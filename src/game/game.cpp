#include "game.h"

#include <conio.h>

#include "async/processevents.h"


Game::Game()
{
    m_currentMenu = Menu::Main;
    m_isRunning = false;
    m_rooms = {};

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
        }
    });
}

Game::~Game()
{
    for (int i = 0; i < m_rooms.size(); i++) {
        if (m_rooms[i] != nullptr) {
            delete m_rooms[i];
        }
    }

    m_rooms.clear();
}

void Game::addRoom(Room* room)
{
    m_rooms.push_back(room);
}

void Game::addRoom(const String& description, IItem* item, const RoomPos& roomPos)
{
    Room* room = new Room(description, item, roomPos);
    m_rooms.push_back(room);
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
        int c = getch();
        if (c == KEY_ESCAPE) {
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
                if (c == KEY_m) {
                    m_currentMenu = Menu::MoveRoom;
                    m_currentMenuChanged.send(m_currentMenu);
                }
                break;
            case Menu::MoveRoom:
                break;
            case Menu::Inventory:
                break;
            case Menu::Spellbook:
                break;
        }
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
