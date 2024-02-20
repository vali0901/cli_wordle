#include "../include/solution.h"
#include<bits/stdc++.h> 

Solution::Solution() {
    this->word = "";
    this->pattern = "_____";
    matchingLetters = std::vector<int8_t>(26, 0);
}

std::string Solution::getPattern() {
    return this->pattern;
}

void Solution::setWord(std::string word) {
    this->word = word;
    memset(matchingLetters.data(), 0, 26);
    for(auto &c : word) {
        matchingLetters[c - 'a']++;
    }
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
            pattern[i] = guess[i] - ('a' - 'A');
            matchingLettersGuess[guess[i] - 'a']--;
            continue;
        }
    }

    for(int i = 0; i < 5; i++) {        
        if(guess[i] == this->word[i])
            continue;

        // yellow letter
        if(guess[i] != this->word[i]
            && this->word.find(guess[i]) != std::string::npos
            && matchingLettersGuess[guess[i] - 'a'] > 0) {
            pattern[i] = guess[i];
            matchingLettersGuess[guess[i] - 'a']--;

            continue;
        }
    }

    return false;
}
