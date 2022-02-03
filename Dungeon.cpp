//
// Created by gpelletier on 2022-01.
//

#include "Dungeon.h"
#include "Item.cpp"

/**
 * Dungeon class constructor
 * @param rows: number of rows in dungeon
 * @param cols: number of column in dungeon
 * @param rEnemies: reference to a list of GameCharacters
 * @param rItems: reference to a list of Items
 * @param rFinalBoss: reference to a final boss GameCharacter
 */
Dungeon::Dungeon(int rows, int cols, vector<GameCharacter> &rEnemies, vector<Item> &rItems, GameCharacter &rFinalBoss) :
        m_rows(rows),
        m_cols(cols) {

    m_NbEnemies = 0;
    srand(time(nullptr));

    // Initialize dynamic array of rooms
    m_rooms = new Room *[m_rows];
    for (int i = 0; i < m_rows; i++) {
        m_rooms[i] = new Room[m_cols];
    }

    // Creates a room for all elements of the array
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            m_rooms[r][c] = Room{r, c};
        }
    }

    // Adds enemies to random rooms in the array
    for (auto &enemy : rEnemies) {
        m_rooms[rand() % m_rows][rand() % m_cols].enemies.push_back(enemy);
        m_NbEnemies++;
    }

    // Adds items to random rooms in the array
    for (auto &item : rItems) {
        m_rooms[rand() % m_rows][rand() % m_cols].items.push_back(item);
    }

    // Set the final boss in the top left room
    m_rooms[0][0].enemies.push_back(rFinalBoss);
    m_NbEnemies++;
}

/**
 * Dungeon class destructor
 */
Dungeon::~Dungeon() {
    for (int i = 0; i < m_rows; i++)
        delete[] m_rooms[i];
    delete[] m_rooms;
}
