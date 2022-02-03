//
// Created by gpelletier on 2022-01.
//

#include "GameCharacter.h"

/**
 * GameCharacter constructor
 * @param name: name of character
 * @param health: health of character
 * @param damage: base damage of character
 */
GameCharacter::GameCharacter(string name, int health, int damage) : m_name(move(name)),
                                                                    m_maxHealth(health),
                                                                    m_currentHealth(health),
                                                                    m_damage(damage) {

}

/**
 * Subtracts an amount from current health and clamps the value
 * @param amount: amount to subtract from current health
 */
void GameCharacter::TakeDamage(int amount) {
    m_currentHealth -= amount;
    m_currentHealth = clamp(m_currentHealth, 0, m_maxHealth);
}

/**
 * Adds an amount to current health and clamps the value
 * @param amount: amount to add to current health
 */
void GameCharacter::HealDamage(int amount) {
    m_currentHealth += amount;
    m_currentHealth = clamp(m_currentHealth, 0, m_maxHealth);
}

/**
 * Checks the current health of the game character
 * @return true if above 0
 */
bool GameCharacter::IsAlive() const {
    return m_currentHealth > 0;
}

/**
 * Returns the name of the game character
 * @return string name
 */
string GameCharacter::GetName() {
    return m_name;
}

/**
 * Returns the current health of the character
 * @return integer value of the current health
 */
int GameCharacter::GetHealth() const {
    return m_currentHealth;
}

/**
 * Returns the current damage value of the game character
 * @return integer value damage
 */
int GameCharacter::GetDamage() const {
    return m_damage;
}

/**
 * Adds damage amount to the current damage of the character
 * @param amount amount to add to the current damage value
 */
void GameCharacter::AddDamage(int amount) {
    m_damage += amount;
}
