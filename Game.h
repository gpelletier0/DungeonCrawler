//
// Created by gpelletier on 2022-01.
//

#include <vector>
#include "Dungeon.h"
#include "Player.h"
#include "Vector2Int.cpp"

#ifndef DUNGEONCRAWLER_GAME_H
#define DUNGEONCRAWLER_GAME_H

using namespace std;

class Game {

private:
    vector<string> movementActions = {"Move Up", "Move Down", "Move Left", "Move Right"};
    vector<string> attackActions = {"Attack", "Retreat"};
    vector<string> pickupActions = {"Pickup Item", "Keep Moving"};

    Dungeon *m_pDungeon;
    Player *m_pPlayer;

    vector<string> GetMovementActions(Room &rCurrentRoom);

    static void PrintActions(vector<string> &rActions);

    static void PrintActions(vector<GameCharacter> &rActions);

    static void PrintActions(vector<Item> &rActions);

    Vector2Int GetMovementValues(const string &rMovement);

    static void DisplayEnemies(vector<GameCharacter> &enemies);

    void DisplayItems(vector<Item> &rItems);

    void HandleMovementActions();

    void HandleEnemyEncounter();

    void HandleItemsEncounter();

    void CombatLoop(Room &room);

    GameCharacter *GetEnemyInput(vector<GameCharacter> &rEnemies);

    Item *GetItemInput(vector<Item> &rItems);

    void PlayerTurn(GameCharacter &rChosenEnemy, Room &rCurrentRoom);

    void EnemyTurn(vector<GameCharacter> &rEnemies);

    void DamagePlayer(GameCharacter &rEnemy);

public:
    bool isGameOver;

    Game(Player *pPlayer, Dungeon *pDungeon);

    ~Game();

    void GameLoop();

    void UseItem(Item &rItem);

    void DisplayPlayerStats();
};

#endif //DUNGEONCRAWLER_GAME_H
