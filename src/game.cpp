#include <iostream>
#include <fstream>
#include "../include/game.h"

Game *Game::instance = NULL;

Game::Game() {
    srand(time(NULL));
    this->test = 0;
    wort = new Wort(trie, sol);
}

Game::~Game() {
    delete wort;
}

Game* Game::getInstance() {
    std::cout << "Creating instance\n";
    if (Game::instance == NULL) {
        Game::instance = new Game();
    }
    return Game::instance;
}

void Game::removeInstance() {
    if (Game::instance != NULL) {
        delete Game::instance;
        Game::instance = NULL;
    }
}

void Game::populateTrie(std::string filename) {
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        this->trie.insert(word);
    }
    file.close();
}

void Game::testTrie() {
    //this->trie.print();
    std::cout << this->trie.getRandom() << "\n";
}

void Game::startGame() {
    wort->init(trie);
    std::string word = this->trie.getRandom();
    sol.setWord(word);
    std::cout << "The Game has started, guess the word\n";
    std::string guess;
    int nr_guesses = 0;
    while (nr_guesses < 5) {
        std::vector<std::string> suggestions = wort->suggest();
        std::cout << "Wort suggests: ";
        for(auto word : suggestions)
            std::cout << word << ", ";

        std::cout << "\n";
    //std::cout << "The word is " << word << "\n";


        //std::cout << "Nr words is trie:" << trie.count() << "\n";

        do {
            std::cin >> guess;
            if (guess.length() != 5 || !trie.find(guess))
                std::cout << "Not a valid word, try again!\n";
            else
                break;
        } while(1);

        bool found = sol.guess(guess);
        std::cout << guess << "\t" << sol.getPattern() << "\t" << "Remaining guesses: " << 5 - nr_guesses - 1 << "\n";
        
        if (found) {
            std::cout << "Congratulations, you guessed the word!\n";
            return;
        }

        wort->guess(guess, sol.getPattern());
        nr_guesses++;
    }

    std::cout << "You lost! The word was " << word << "\n";

}