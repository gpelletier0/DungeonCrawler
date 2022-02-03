//
// Created by gpelletier on 2022-01.
//

#include "Player.h"

/**
 * Player class constructor
 * @param name
 * @param health
 * @param damage
 */
Player::Player(const string &name, int health, int damage) : GameCharacter(name, health, damage) {

}

/**
 * Player class destructor
 */
Player::~Player() {
    currentRoomPtr = nullptr;
    previousRoomPtr = nullptr;
}

/**
 * Adds an amount to the player's health
 * @param amount: amount to add to health
 */
void Player::Heal(int amount) {
    HealDamage(amount);
}

/**
 * Moves the player to a room
 * @param pRoom: pointer to a room
 */
void Player::MoveToRoom(Room *pRoom) {
    previousRoomPtr = currentRoomPtr;
    currentRoomPtr = pRoom;
}

/**
 * Moves the player to the previous room
 */
void Player::Retreat() {
    Room *temp = currentRoomPtr;
    currentRoomPtr = previousRoomPtr;
    previousRoomPtr = temp;
}
