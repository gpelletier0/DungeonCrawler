//
// Created by gpelletier on 2022-01.
//

#include <iostream>
#include <vector>
#include "Game.h"

/**
 * Template for console input loop
 * @tparam T: type of input
 * @param rActions: list of possible actions
 * @return selected action from list
 */
template<typename T>
T *GetActionInput(vector<T> &rActions) {

    int input;
    while (true) {
        cout << "> ";
        cin >> input;
        if (cin && input - 1 >= 0 && input - 1 <= rActions.size() - 1) {
            return &rActions[input - 1];
        } else {
            cout << "Invalid input...\n";
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
}

/**
 * Game Class Constructor
 * @param pPlayer pointer to Player object
 * @param pDungeon pointer to Dungeon object
 */
Game::Game(Player *pPlayer, Dungeon *pDungeon) : m_pPlayer(pPlayer),
                                                 m_pDungeon(pDungeon) {
    isGameOver = false;

    // Set Player start room to the last room
    m_pPlayer->currentRoomPtr = &m_pDungeon->m_rooms[m_pDungeon->m_rows - 1][m_pDungeon->m_cols - 1];
}

/**
 * Game Class Destructor
 */
Game::~Game() {
    m_pDungeon = nullptr;
    m_pPlayer = nullptr;
}

/**
 * Main Game Loop
 */
void Game::GameLoop() {

    Room *currentRoom = m_pPlayer->currentRoomPtr;

    if (m_pDungeon->GetNbEnemies() > 0) {
        cout << "\nYour are in room " << m_pPlayer->currentRoomPtr->row << " " << m_pPlayer->currentRoomPtr->col
             << "\n";

        if (currentRoom->enemies.empty()) {
            HandleMovementActions();
        } else {
            HandleEnemyEncounter();
        }
    } else {
        cout << "\nThe dungeon has been cleared, " << m_pPlayer->GetName() << " is victorious!\n";
        isGameOver = true;
    }
}

/**
 * Creates a list of possible movements in the current room
 * @param rCurrentRoom: Reference to the current room
 * @return list of strings of available movements in the current room
 */
vector<string> Game::GetMovementActions(Room &rCurrentRoom) {

    vector<string> actions;

    if (rCurrentRoom.row > 0) { // Up
        actions.push_back(movementActions[0]);
    }
    if (rCurrentRoom.row < m_pDungeon->m_rows - 1) { // Down
        actions.push_back(movementActions[1]);
    }
    if (rCurrentRoom.col > 0) { // Left
        actions.push_back(movementActions[2]);
    }
    if (rCurrentRoom.col < m_pDungeon->m_cols - 1) { // Right
        actions.push_back(movementActions[3]);
    }

    return actions;
}

/**
 * Prints a list of strings actions to console
 * @param rActions: reference to a list of strings
 */
void Game::PrintActions(vector<string> &rActions) {
    for (int i = 0; i < rActions.size(); i++) {
        cout << i + 1 << ". " << rActions[i] << endl;
    }
}

/**
 * Prints a list of GameCharacters actions to console
 * @param rActions: reference list of game characters
 */
void Game::PrintActions(vector<GameCharacter> &rActions) {
    for (int i = 0; i < rActions.size(); i++) {
        cout << i + 1 << ". " << rActions[i].GetName() << endl;
    }
}

/**
 * Turns a movement string into a movement vector
 * @param rMovement: reference to a movement string
 * @return Vector2Int movement vector
 */
Vector2Int Game::GetMovementValues(const string &rMovement) {

    Vector2Int movementValues = Vector2Int();

    if (rMovement == movementActions[0]) { // Up
        movementValues.x = -1;
    } else if (rMovement == movementActions[1]) { // Down
        movementValues.x = 1;
    } else if (rMovement == movementActions[2]) { // Left
        movementValues.y = -1;
    } else if (rMovement == movementActions[3]) { // Right
        movementValues.y = 1;
    }

    return movementValues;
}

/**
 * Movement actions handler function
 */
void Game::HandleMovementActions() {

    vector<string> actions = GetMovementActions(*m_pPlayer->currentRoomPtr);
    Room *currentRoom = m_pPlayer->currentRoomPtr;

    if (!currentRoom->items.empty()) {
        HandleItemsEncounter();
    }

    cout << "Where do you want to go next?\n";
    PrintActions(actions);

    string *chosenAction = GetActionInput(actions);
    Vector2Int movementValues = GetMovementValues(*chosenAction);

    Room *newRoom = &m_pDungeon->m_rooms[currentRoom->row + movementValues.x][currentRoom->col + movementValues.y];
    m_pPlayer->MoveToRoom(newRoom);
}

/**
 * Enemy encounter handler function
 */
void Game::HandleEnemyEncounter() {

    Room *currentRoom = m_pPlayer->currentRoomPtr;
    vector<GameCharacter> &enemies = currentRoom->enemies;

    cout << (enemies.size() == 1 ? "There is an enemy!" : "There are enemies!") << endl;
    DisplayEnemies(enemies);

    while (!isGameOver && !currentRoom->enemies.empty()) {
        DisplayPlayerStats();
        cout << "What would you like to do?\n";

        PrintActions(attackActions);
        string *chosenAction = GetActionInput(attackActions);

        if (*chosenAction == attackActions[0]) {
            CombatLoop(*currentRoom);
        } else {
            if (m_pPlayer->previousRoomPtr != nullptr) {
                m_pPlayer->Retreat();
            } else {
                cout << "Unable to retreat\n";
            }
            break;
        }
    }
}

/**
 * Main combat loop
 * @param currentRoom: reference to the current room
 */
void Game::CombatLoop(Room &currentRoom) {

    GameCharacter *chosenEnemy = GetEnemyInput(currentRoom.enemies);
    if (chosenEnemy != nullptr) {
        PlayerTurn(*chosenEnemy, currentRoom);
    }

    EnemyTurn(currentRoom.enemies);
}

/**
 * Displays a list of enemies to the console
 * @param enemies
 */
void Game::DisplayEnemies(vector<GameCharacter> &enemies) {

    for (auto &enemy : enemies) {
        cout << "\n" << enemy.GetName() << " [ HP:" << enemy.GetHealth() << " DMG:" << enemy.GetDamage() << " ]";
    }
    cout << "\n\n";
}

/**
 * Retrieves player battle input from console
 * @param rEnemies: reference to a list of enemies
 * @return selected enemy or null
 */
GameCharacter *Game::GetEnemyInput(vector<GameCharacter> &rEnemies) {

    if (!rEnemies.empty()) {
        if (rEnemies.size() > 1) {
            cout << "\nWho would you like to attack?\n";
            PrintActions(rEnemies);
            return GetActionInput(rEnemies);
        }

        return &rEnemies[0];
    }

    return nullptr;
}

/**
 * Player battle damage handler function
 * @param rChosenEnemy: reference to an enemy
 * @param rCurrentRoom: reference to the current room
 */
void Game::PlayerTurn(GameCharacter &rChosenEnemy, Room &rCurrentRoom) {

    cout << "\nYou hit the " << rChosenEnemy.GetName() << " for " << m_pPlayer->GetDamage() << " damage\n";
    rChosenEnemy.TakeDamage(m_pPlayer->GetDamage());

    if (!rChosenEnemy.IsAlive()) {
        cout << "You have killed the " << rChosenEnemy.GetName() << "!\n";
        rCurrentRoom.RemoveEnemy(rChosenEnemy);
        m_pDungeon->RemoveAnEnemy();
    }
}

/**
 * Enemy battle turn handler function
 * @param rEnemies
 */
void Game::EnemyTurn(vector<GameCharacter> &rEnemies) {

    if (!rEnemies.empty()) {
        for (auto &enemy : rEnemies) {
            DamagePlayer(enemy);
        }

        DisplayEnemies(rEnemies);
    }
}

/**
 * Enemy battle damage handler function
 * @param rEnemy: reference to an enemy
 */
void Game::DamagePlayer(GameCharacter &rEnemy) {

    cout << "The " << rEnemy.GetName() << " hits you for " << rEnemy.GetDamage() << "\n";
    m_pPlayer->TakeDamage(rEnemy.GetDamage());

    if (!m_pPlayer->IsAlive()) {
        cout << "\nYou have died...\n";
        isGameOver = true;
        return;
    }
}

/**
 * Player item encounter handler function
 */
void Game::HandleItemsEncounter() {

    Room *currentRoom = m_pPlayer->currentRoomPtr;
    vector<Item> &items = currentRoom->items;

    cout << (items.size() == 1 ? "There is an item!" : "There are items!") << endl;

    while (!items.empty()) {
        DisplayItems(items);

        cout << "What would you like to do?\n";

        PrintActions(pickupActions);
        string *chosenAction = GetActionInput(pickupActions);
        cout << endl;

        if (*chosenAction == pickupActions[0]) {
            Item *item = GetItemInput(items);
            if (item != nullptr) {
                UseItem(*item);
                currentRoom->RemoveItem(*item);
            }
        } else {
            break;
        }
    }
}

/**
 * Displays a list of rItems to the console
 * @param rItems: reference to a list of items
 */
void Game::DisplayItems(vector<Item> &rItems) {

    cout << "\n";

    for (auto &item : rItems) {
        cout << item.name << " [ ";

        if (item.damage > 0) {
            cout << "DMG:" << item.damage << " ";
        }
        if (item.health > 0) {
            cout << "HP:" << item.health << " ";
        }
        cout << "]\n";
    }

    cout << "\n";
    DisplayPlayerStats();
}

/**
 * Retrieves player item input from console
 * @param rItems: reference to a list of items
 * @return selected item or null
 */
Item *Game::GetItemInput(vector<Item> &rItems) {

    if (!rItems.empty()) {
        if (rItems.size() > 1) {
            cout << "What item would you like to pick up?\n";
            PrintActions(rItems);
            return GetActionInput(rItems);
        }

        return &rItems[0];
    }

    return nullptr;
}

/**
 * Prints a list of actions to console
 * @param rActions: reference to a list of actions
 */
void Game::PrintActions(vector<Item> &rActions) {

    for (int i = 0; i < rActions.size(); i++) {
        cout << i + 1 << ". " << rActions[i].name << endl;
    }
}

/**
 * Use item function
 * @param rItem: reference to an item
 */
void Game::UseItem(Item &rItem) {

    if (rItem.health > 0) {
        m_pPlayer->Heal(rItem.health);
    }
    if (rItem.damage > 0) {
        m_pPlayer->AddDamage(rItem.damage);
    }
    DisplayPlayerStats();
}

/**
 * Displays player stats to console
 */
void Game::DisplayPlayerStats() {
    cout << m_pPlayer->GetName() << " [ HP:" << m_pPlayer->GetHealth() << " DMG:" << m_pPlayer->GetDamage() << " ]\n\n";
}
