#include <iostream>
#include <fstream>
#include "../include/game.h"
#include <bits/stdc++.h>

Game *Game::instance = NULL;

Game::Game()
{
    srand(time(NULL));
    wort = new Wort();
}

Game::~Game()
{
    delete wort;
}

Game *Game::getInstance()
{
    if (Game::instance == NULL)
    {
        Game::instance = new Game();
    }
    return Game::instance;
}

void Game::removeInstance()
{
    if (Game::instance != NULL)
    {
        delete Game::instance;
        Game::instance = NULL;
    }
}

void Game::populateTrie(std::string filename)
{
    std::ifstream file(filename);
    std::string word;
    while (file >> word)
    {
        this->trie.insert(word);
    }
    file.close();
}

bool Game::match(std::string guess, std::string pattern)
{
    if (guess.length() != pattern.length())
        return false;

    for (int i = 0; i < pattern.length(); i++)
    {
        if (pattern[i] != '_' && (pattern[i] < 'a' || pattern[i] > 'z') && (pattern[i] < 'A' || pattern[i] > 'Z'))
            return false;

        if (pattern[i] != '_' && pattern[i] != guess[i] && pattern[i] != guess[i] - ('a' - 'A'))
            return false;
    }

    return true;
}

void Game::startGame()
{

    while (1)
    {
        // select game mode
        std::cout << "Select game mode: (type a number)\n";
        std::cout << "1. Wordle with no suggestions\n";
        std::cout << "2. Wordle with Wort's suggestions\n";
        std::cout << "3. Only Wort's suggestions\n";
        std::cout << "4. Exit\n";

        std::string mode;
        do
        {
            getline(std::cin, mode);
            if (mode != "1" && mode != "2" && mode != "3" && mode != "4")
                std::cout << "Invalid mode, try again!\n";
            else
                break;
        } while (1);

        switch (atoi(mode.c_str()))
        {
        case 1:
            gamemode1();
            break;

        case 2:
            gamemode2();
            break;

        case 3:
            gamemode3();
            break;

        case 4:
            return;
            break;

        default:
            std::cout << "Invalid mode\n";
            break;
        }
    }
}


void Game::gamemode1()
{
    std::string word = this->trie.getRandom();
    sol.setWord(word);
    std::cout << "The Game has started, guess the word\n";

    std::string guess;
    bool found;
    int nr_guesses = 0;
    while (nr_guesses < 6)
    {
        do
        {
            std::cin >> guess;
            if (guess.length() != 5 || !trie.find(guess))
                std::cout << "Not a valid word, try again!\n";
            else
                break;
        } while (1);

        found = sol.guess(guess);
        std::cout << guess << "\t" << sol.getPattern() << "\t"
                  << "Remaining guesses: " << 6 - nr_guesses - 1 << "\n";

        if (found)
        {
            std::cout << "Congratulations, you guessed the word!\n\n\n";
            break;
        }

        nr_guesses++;
    }

    if (!found)
        std::cout << "You lost! The word was " << word << "\n\n\n";

    getline(std::cin, guess);
}

void Game::gamemode2()
{
    wort->init(trie);
    std::string word = this->trie.getRandom();
    sol.setWord(word);

    std::cout << "The Game has started, guess the word\n";

    std::string guess;
    bool found;
    int nr_guesses = 0;
    while (nr_guesses < 6)
    {
        std::vector<std::string> suggestions = wort->suggest();
        std::cout << "Wort suggests: ";
        for (auto word : suggestions)
            std::cout << word << " ";
        std::cout << "\n";

        do
        {
            std::cin >> guess;
            if (guess.length() != 5 || !trie.find(guess))
                std::cout << "Not a valid word, try again!\n";
            else
                break;
        } while (1);

        found = sol.guess(guess);
        std::cout << guess << "\t" << sol.getPattern() << "\t"
                  << "Remaining guesses: " << 6 - nr_guesses - 1 << "\n";

        if (found)
        {
            std::cout << "Congratulations, you guessed the word!\n\n\n";
            break;
        }

        wort->guess(guess, sol.getPattern());
        nr_guesses++;
    }

    if (!found)
        std::cout << "You lost! The word was " << word << "\n\n\n";

    getline(std::cin, guess);
}

void Game::gamemode3()
{
    wort->init(trie);
    std::string guess, pattern;
    bool exit = false;
    while (1)
    {
        std::vector<std::string> suggestions = wort->suggest();
        std::cout << "Wort suggests: ";
        for (auto word : suggestions)
            std::cout << word << " ";
        std::cout << "\n";

        std::cout << "Enter a guess or type 'exit' to quit\n";
        do
        {
            std::cin >> guess;
            if (guess == "exit")
            {
                exit = true;
                break;
            }
            if (guess.length() != 5 || !trie.find(guess))
                std::cout << "Not a valid word, try again!\n";
            else
                break;
        } while (1);

        if (exit)
            break;

        std::cout << "Enter the pattern or type 'exit' to quit\n";
        do
        {
            std::cin >> pattern;

            if (pattern == "exit")
            {
                exit = true;
                break;
            }

            if (pattern.length() != 5 || !match(guess, pattern))
                std::cout << "Not a valid pattern, try again!\n";
            else
                break;
        } while (1);

        if (exit)
            break;

        std::string guessCopy = guess;
        transform(guessCopy.begin(), guessCopy.end(), guessCopy.begin(), ::toupper);

        if (guessCopy == pattern)
        {
            std::cout << "Congratulations, you guessed the word!\n\n\n";
            break;
        }

        wort->guess(guess, pattern);
    }

    getline(std::cin, guess);
}
