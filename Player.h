//
// Created by gpelletier on 2022-01.
//

#include "GameCharacter.h"
#include "Room.cpp"

#ifndef DUNGEONCRAWLER_PLAYER_H
#define DUNGEONCRAWLER_PLAYER_H

using namespace std;

class Player : public GameCharacter {

public:
    Room *currentRoomPtr = nullptr;
    Room *previousRoomPtr = nullptr;

    Player(const string &name, int health, int damage);

    ~Player();

    void Heal(int amount);

    void MoveToRoom(Room *pRoom);

    void Retreat();
};

#endif //DUNGEONCRAWLER_PLAYER_H
