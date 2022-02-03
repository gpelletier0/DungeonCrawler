//
// Created by gpelletier on 2022-01.
//

#include <vector>
#include "Room.cpp"
#include "Item.cpp"

#ifndef DUNGEONCRAWLER_DUNGEON_H
#define DUNGEONCRAWLER_DUNGEON_H

using namespace std;

class Dungeon {

private:
    int m_NbEnemies;

public:
    int m_rows;
    int m_cols;
    Room **m_rooms;

    Dungeon(int rows, int cols, vector<GameCharacter> &rEnemies, vector<Item> &rItems, GameCharacter &rFinalBoss);

    ~Dungeon();

    void RemoveAnEnemy() { m_NbEnemies--; }

    int GetNbEnemies() const { return m_NbEnemies; }
};

#endif //DUNGEONCRAWLER_DUNGEON_H
