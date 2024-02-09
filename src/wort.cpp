#include "../include/game.h"
#include <string>
#include <iostream>

Game::Wort::Wort(Trie &trie, Solution &sol) : trie(trie), sol(sol) {}

std::vector<std::string> Game::Wort::suggest() {
    std::vector<std::string> result;
    for(auto _ = 0; _ < 3; _++) {
        std::string suggestion;
        bool sw = suggestHelper(trie.getRoot(), 0, suggestion);
        if(!sw)
            break;
        result.push_back(suggestion);
    }
    return result;
}

bool Game::Wort::suggestHelper(TrieNode *node, int depth, std::string &result) {
    if(depth == 5 && node->isEnd) {
        return true;
    }

    bool sw = true;

    int nr_tries = 0;

    while(nr_tries < 26) {
        int poolIndex;
        int trieIndex;
        int counter = 0;
        do {
            poolIndex = rand() % sol.getPool()[depth].size();
            trieIndex = sol.getPool()[depth][poolIndex] - 'a';
            counter++;
            if(counter > 26)
                return false;
        } while(node->children[trieIndex] == NULL);

        result += node->children[trieIndex]->c;
        sw = suggestHelper(node->children[trieIndex], depth + 1, result);
        if(sw)
            return true;
        result.pop_back();
        nr_tries++;
    }

    return false;
}