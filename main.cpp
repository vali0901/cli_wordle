#include <iostream>
#include <bits/stdc++.h>
#include "include/game.h"

#define DICTIONARY "words.txt"

int main() {
    Game *game = Game::getInstance();

    game->populateTrie(DICTIONARY);
    game->startGame();
    Game::removeInstance();
    
    return 0;
}