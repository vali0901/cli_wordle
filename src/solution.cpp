#include "../include/solution.h"
#include<bits/stdc++.h> 

Solution::Solution() {
    this->pool = std::vector<std::vector<char>>(5, std::vector<char>(26, 'a'));
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 26; j++) {
            this->pool[i][j] = 'a' + j;
        }
    }

    this->word = "";
    this->pattern = "_____";
    matchingLetters = std::vector<int8_t>(26, 0);
}

Solution::~Solution() {
}

std::string Solution::getPattern() {
    return this->pattern;
}

void Solution::setWord(std::string word) {
    this->word = word;
    for(auto &c : word) {
        matchingLetters[c - 'a']++;
    }
}

std::vector<std::vector<char>> Solution::getPool() {
    return this->pool;
}

bool Solution::guess(std::string guess) {
    if(guess == this->word) {
        this->pattern = this->word;
        transform(this->pattern.begin(), this->pattern.end(), this->pattern.begin(), ::toupper);
        return true;
    }
    pattern = "_____";

    std::vector<int8_t> matchingLettersGuess = this->matchingLetters;

    for(int i = 0; i < 5; i++) {
        // green letter
        if(guess[i] == this->word[i]) {
            pool[i].clear();
            pool[i].push_back(guess[i]);
            pattern[i] = guess[i] - ('a' - 'A');
            matchingLettersGuess[guess[i] - 'a']--;
            continue;
        }
    }

    for(int i = 0; i < 5; i++) {        
        // yellow letter
        // green letter
        if(guess[i] == this->word[i]) {
            continue;
        }
        if(guess[i] != this->word[i]
            && this->word.find(guess[i]) != std::string::npos) {
                for(auto it = pool[i].begin(); it != pool[i].end(); it++) {
                    if(*it == guess[i]) {
                        pool[i].erase(it);
                        break;
                    }
                }
            if(matchingLettersGuess[guess[i] - 'a'] > 0) {
                pattern[i] = guess[i];
                matchingLettersGuess[guess[i] - 'a']--;
            }
            continue;
        }

        // gray letter
        for(auto &pool_c : pool) {
            for(auto it = pool_c.begin(); it != pool_c.end(); it++) {
                if(*it == guess[i]) {
                    pool_c.erase(it);
                    break;
                }
            }
        }   
    }

    return false;
}
