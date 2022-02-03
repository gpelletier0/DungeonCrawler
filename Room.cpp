//
// Created by gpelletier on 2022-01.
//

#include <vector>
#include "GameCharacter.h"
#include "Item.cpp"

#ifndef ROOM_CPP
#define ROOM_CPP

using namespace std;

struct Room {

    int row;
    int col;
    vector<GameCharacter> enemies;
    vector<Item> items;

    /**
     * Template to remove an element from a vector of elements
     * @tparam T: type of element
     * @param rElem: reference to an element to remove
     * @param rVec:  reference to a vector to remove element from
     */
    template<typename T>
    void Remove(T &rElem, vector<T> &rVec) {
        auto index = &rElem - &rVec[0];
        if (index <= rVec.size()) {
            auto it = rVec.begin() + index;
            rVec.erase(it);
        }
    }

    /**
     * Removes an enemy from the enemies list
     * @param rChosenEnemy: reference to an enemy
     */
    void RemoveEnemy(GameCharacter &rChosenEnemy) {
        Remove(rChosenEnemy, enemies);
    }

    /**
     * Removes an item from the items list
     * @param item: reference to an item
     */
    void RemoveItem(Item &item) {
        Remove(item, items);
    }
};

#endif