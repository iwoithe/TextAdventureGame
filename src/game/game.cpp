#include "game.h"

#include <conio.h>
#include <cstdlib>
#include <time.h>

#include "async/processevents.h"

#include "global/algorithms.h"
#include "global/delete.h"
#include "global/ints.h"
#include "global/log.h"

#include "dispatcher/dispatcher.h"

#include "items/appleitem.h"
#include "items/breaditem.h"
#include "items/iitem.h"
#include "items/items.h"
#include "items/lavabucketitem.h"
#include "items/spellpotionitem.h"
#include "items/stubitem.h"

#include "player/player.h"

#include "spells/ispell.h"
#include "spells/killspell.h"
#include "spells/spells.h"

Game::Game()
{
    srand(time(0));

    m_playerInventorySize = 0;
    m_playerSpellsSize = 0;

    loadAvailableItems();
    loadAvailableSpells();

    initGameObjects();

    m_isRunning = false;
    m_rooms = {};
    addRoom("Lobby", nullptr, RoomPos(0, 0));
    m_currentRoom = findRoom(RoomPos(0, 0));

    init();

    gameIntro();
    setMenu(Menu::Main);
}

Game::~Game()
{
    for (IGameObject* gameObject : m_gameObjects) {
        gameObject->deInit();
    }

    DEL_STD_VEC(m_gameObjects);

    m_currentRoom = nullptr;
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
    Player* player = new Player();

    player->inventorySizeChanged().onReceive(nullptr, [&](int newSize) {
        m_playerInventorySize = newSize;
    });

    player->spellSizeChanged().onReceive(nullptr, [&](int newSize) {
        m_playerSpellsSize = newSize;
    });

    addGameObject(player);

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
    addRoom("Hello", getRandomItem(), roomPos);
}

Room* Game::findRoom(const RoomPos& roomPos)
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
    String("Press [s] to enter the spellbook menu").writeToConsole();
    String("Press [l] to enter the list menu (view all available items and spells)").appendColor(Color::Default, ColorLayer::Foreground).writeToConsole();
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
        case Menu::SpellMenu:
            menuTitleText.append("[Spell Menu]");
            break;
        case Menu::ListMenu:
            menuTitleText.append("[List Menu]");
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
        case Menu::SpellMenu:
            displaySpellMenuInstructions();
            break;
        case Menu::ListMenu:
            displayListMenuInstructions();
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
    infoText.appendColor(Color::Default, ColorLayer::Foreground);
    infoText.writeToConsole();
    dispatcher()->dispatch("player-list-inventory", Parameters());
    String("Enter item number:  ").writeToConsole(false);
}

void Game::displaySpellMenuInstructions()
{
    dispatcher()->dispatch("player-list-spells", Parameters());
    String("Enter spell number:  ").writeToConsole(false);
}

void Game::displayListMenuInstructions() const
{
    String infoText;
    infoText.append("Listing all available items and spells\n");
    infoText.append("Items:\n");

    for (const String& itemName : m_availableItemsNames) {
        infoText.append("- ").append(itemName).append("\n");
    }

    infoText.append("\nSpells:\n");

    for (const String& spellName : m_availableSpellsNames) {
        infoText.append("- ").append(spellName).append("\n");
    }

    infoText.append("\nType the name of the spell and hit [Enter] to find out more\nNote: searching is case-sensitive\n");
    infoText.append("Press [Esc] or [q] to go back to [Main Menu]");
    infoText.writeToConsole();
}

void Game::loadAvailableItems()
{
    IItem* item;
    for (int i = 0; i < ITEM_TYPE_LENGTH; i++) {
        switch (i) {
            case ItemType::Apple:
                item = new AppleItem();
                goto appendItemName;
            case ItemType::Bread:
                item = new BreadItem();
                goto appendItemName;
            case ItemType::LavaBucket:
                item = new LavaBucketItem();
                goto appendItemName;
            case ItemType::SpellPotion:
                item = new SpellPotionItem();
                goto appendItemName;
            case ItemType::None:
                break;
            appendItemName:
                m_availableItemsNames.push_back(item->name());
                m_availableItemsDescriptions.push_back(item->description());
                delete item;
                break;
        }
    }

    std::sort(m_availableItemsNames.begin(), m_availableItemsNames.end(), [=](const String& a, const String& b) {return a < b;});
    std::sort(m_availableItemsDescriptions.begin(), m_availableItemsDescriptions.end(), [=](const String& a, const String& b) {return a < b;});
}

void Game::loadAvailableSpells()
{
    ISpell* spell;
    for (int i = 0; i < SPELL_TYPE_LENGTH; i++) {
        switch (i) {
            case SpellType::Kill:
                spell = new KillSpell();
                goto appendSpellName;
            appendSpellName:
                m_availableSpellsNames.push_back(spell->name());
                m_availableSpellsDescription.push_back(spell->description());
                delete spell;
                break;
        }
    }

    std::sort(m_availableSpellsNames.begin(), m_availableSpellsNames.end(), [=](const String& a, const String& b) {return a < b;});
    std::sort(m_availableSpellsDescription.begin(), m_availableSpellsDescription.end(), [=](const String& a, const String& b) {return a < b;});
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
            case Menu::SpellMenu:
                handleSpellMenu(key);
                break;
            case Menu::ListMenu:
                handleListMenu(key);
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
            case Menu::SpellMenu:
            case Menu::ListMenu:
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
            setMenu(Menu::SpellMenu);
            break;
        case KEY_l:
            setMenu(Menu::ListMenu);
            break;
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

        Room* r = findRoom(newPos);
        if (r == nullptr) {
            addRandomRoom(newPos);
            m_currentRoom = findRoom(newPos);
        } else {
            m_currentRoom = r;
        }

        // Flush and end the current line
        String().writeToConsole();
        if (m_currentRoom->isEmpty()) {
            String("Room (").append(m_currentRoom->roomPos().x).append(", ").append(m_currentRoom->roomPos().y).append(") is empty").writeToConsole();
        } else {
            String("Room (").append(m_currentRoom->roomPos().x).append(", ").append(m_currentRoom->roomPos().y).append(") has item ").append(m_currentRoom->item()->name()).writeToConsole();
        }

        dispatcher()->dispatch("player-move-room", Parameters({ Any(dir) }));
        if (m_currentRoom) {
            dispatcher()->dispatch("player-add-item-to-inventory", Parameters({ Any(m_currentRoom->item()) }));
            m_currentRoom->removeItem();
        }

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
    if (key == KEY_ENTER && _m__himNum > 0 && _m__himNum <= m_playerInventorySize) {
        // Flush and end the current line
        String().writeToConsole();
        
        // _m__himNum - 1 as Player::useInventoryItem uses 0-index, but items listed out as index + 1
        dispatcher()->dispatch("player-use-inventory-item", Parameters({ Any(_m__himNum - 1) }));

        _m__himNum = 0;
        setMenu(Menu::Main);
    }

    if (key == KEY_BACKSPACE) {
        String("\033[").append(numDigitsInNum(_m__himNum)).append("D\033[0K").writeToConsole(false);
        _m__himNum /= 10;
        String(_m__himNum).writeToConsole(false);
    }

    switch (key) {
        case KEY_0:
            _m__himNum = concatenateInts(_m__himNum, 0);
            goto finally;
        case KEY_1:
            _m__himNum = concatenateInts(_m__himNum, 1);
            goto finally;
        case KEY_2:
            _m__himNum = concatenateInts(_m__himNum, 2);
            goto finally;
        case KEY_3:
            _m__himNum = concatenateInts(_m__himNum, 3);
            goto finally;
        case KEY_4:
            _m__himNum = concatenateInts(_m__himNum, 4);
            goto finally;
        case KEY_5:
            _m__himNum = concatenateInts(_m__himNum, 5);
            goto finally;
        case KEY_6:
            _m__himNum = concatenateInts(_m__himNum, 6);
            goto finally;
        case KEY_7:
            _m__himNum = concatenateInts(_m__himNum, 7);
            goto finally;
        case KEY_8:
            _m__himNum = concatenateInts(_m__himNum, 8);
            goto finally;
        case KEY_9:
            _m__himNum = concatenateInts(_m__himNum, 9);
            goto finally;
        finally:
            // numDigitsInNum(_m__himNum) - 1 as _m__himNum now has one more digit than is outputted
            String("\033[").append(numDigitsInNum(_m__himNum) - 1).append("D\033[0K").append(_m__himNum).writeToConsole(false);
            break;
        default:
            break;
    }
}

void Game::handleSpellMenu(const int& key)
{
    if (key == KEY_ENTER && _m__hsmNum > 0 && _m__hsmNum <= m_playerSpellsSize) {
        // Flush and end the current line
        String().writeToConsole();

        // _m__himNum - 1 as Player::castSpell uses 0-index, but items listed out as index + 1
        dispatcher()->dispatch("player-cast-spell", Parameters({ Any(_m__hsmNum - 1) }));

        _m__hsmNum = 0;
        setMenu(Menu::Main);
    }

    if (key == KEY_BACKSPACE) {
        String("\033[").append(numDigitsInNum(_m__hsmNum)).append("D\033[0K").writeToConsole(false);
        _m__hsmNum /= 10;
        String(_m__hsmNum).writeToConsole(false);
    }

    switch (key) {
        case KEY_0:
            _m__hsmNum = concatenateInts(_m__hsmNum, 0);
            goto finally;
        case KEY_1:
            _m__hsmNum = concatenateInts(_m__hsmNum, 1);
            goto finally;
        case KEY_2:
            _m__hsmNum = concatenateInts(_m__hsmNum, 2);
            goto finally;
        case KEY_3:
            _m__hsmNum = concatenateInts(_m__hsmNum, 3);
            goto finally;
        case KEY_4:
            _m__hsmNum = concatenateInts(_m__hsmNum, 4);
            goto finally;
        case KEY_5:
            _m__hsmNum = concatenateInts(_m__hsmNum, 5);
            goto finally;
        case KEY_6:
            _m__hsmNum = concatenateInts(_m__hsmNum, 6);
            goto finally;
        case KEY_7:
            _m__hsmNum = concatenateInts(_m__hsmNum, 7);
            goto finally;
        case KEY_8:
            _m__hsmNum = concatenateInts(_m__hsmNum, 8);
            goto finally;
        case KEY_9:
            _m__hsmNum = concatenateInts(_m__hsmNum, 9);
            goto finally;
        finally:
            // numDigitsInNum(_m__himNum) - 1 as _m__himNum now has one more digit than is outputted
            String("\033[").append(numDigitsInNum(_m__hsmNum) - 1).append("D\033[0K").append(_m__hsmNum).writeToConsole(false);
            break;
        default:
            break;
    }
}

void Game::handleListMenu(const int& key)
{
    String("> ").writeToConsole(false);
    _m__hlmStr.readFromConsole();
    int itemIndex = binarySearch(m_availableItemsNames, _m__hlmStr);

    if (itemIndex != -1) {
        String text;
        text.append(m_availableItemsNames[itemIndex]);
        text.append(": ");
        text.append(m_availableItemsDescriptions[itemIndex]);
        text.writeToConsole();
        return;
    }

    int spellIndex = binarySearch(m_availableSpellsNames, _m__hlmStr);

    if (spellIndex != -1) {
        String text;
        text.append(m_availableSpellsNames[spellIndex]);
        text.append(": ");
        text.append(m_availableSpellsDescription[spellIndex]);
        text.writeToConsole();
        return;
    }

    String("Item or spell \"").append(_m__hlmStr).append("\" could not be found and probably doesn't exist").writeToConsole();
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
