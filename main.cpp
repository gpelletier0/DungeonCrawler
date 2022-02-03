#include <iostream>
#include "Game.h"
#include "GameCharacter.h"
#include "Player.h"
#include "Item.cpp"

int main() {

    string playerName;
    cout << "Welcome to Dungeon Game, enter your name:\n> ";
    cin >> playerName;

    char c;
    do {
        cin.clear();
        cin.ignore(100, '\n');

        cout << "\nYou have been tasked with clearing the dungeon from foul beings " << playerName << "\n";

        Player player = Player(playerName, 100, 10);

        vector<GameCharacter> enemies = {
                GameCharacter{"Imp", 10, 5},
                GameCharacter{"Orc", 20, 10},
                GameCharacter{"Troll", 30, 15}
        };

        GameCharacter finalBoss = GameCharacter{"Ogre", 40, 20};

        vector<Item> items = {
                Item{"Health Potion", 0, 10},
                Item{"Damage Potion", 10, 0},
                Item{"Berserk Potion", 10, 10}
        };

        Dungeon dungeon = Dungeon(3, 3, enemies, items, finalBoss);
        Game game = Game(&player, &dungeon);

        while (!game.isGameOver) {
            game.GameLoop();
        }

        cout << "Quit (q)?\n"
                "> ";
        cin >> c;
    } while (!cin.good() || c != 'q');

    return 0;
}
