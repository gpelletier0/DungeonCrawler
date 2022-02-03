//
// Created by gpelletier on 2022-01.
//

#include <string>

#ifndef DUNGEONCRAWLER_GAMECHARACTER_H
#define DUNGEONCRAWLER_GAMECHARACTER_H

using namespace std;

class GameCharacter {

private:
    string m_name;
    int m_maxHealth;
    int m_currentHealth;
    int m_damage;

public:
    GameCharacter(string name, int health, int damage);

    void TakeDamage(int amount);

    void HealDamage(int amount);

    void AddDamage(int amount);

    string GetName();

    int GetHealth() const;

    int GetDamage() const;

    bool IsAlive() const;
};


#endif //DUNGEONCRAWLER_GAMECHARACTER_H
