#include "../include/game.h"
#include <string>
#include <iostream>

Game::Wort::Wort(Trie &trie, Solution &sol) : sol(sol) {
    this->trie = trie;
}

void Game::Wort::init(Trie &trie) {
    this->trie = trie;
}

void Game::Wort::guess(std::string guess, std::string pattern) {
    std::vector<char> gray;
    std::vector<std::pair<char, int>> yellow; // needs rethinkning
    std::vector<std::pair<char, int>> green;

    for(int i = 0; i < 5; i++) {
        if(pattern[i] == '_') {
            // if a gray letter has been discovered previously as yellow,
            // we need to mark it as yellow
            bool sw = false;
            for(auto &[c, d] : yellow)
                if(c == guess[i]) {
                    yellow.push_back({c, i});
                    sw = true;
                }

            if(!sw)
                gray.push_back(guess[i]);
        }
        else if(pattern[i] >= 'a' && pattern[i] <= 'z') 
            yellow.push_back({guess[i], i});
        else if(pattern[i] >= 'A' && pattern[i] <= 'Z')
            green.push_back({guess[i], i});
    }

    // for(auto &[c, d] : yellow) {
    //     for(auto it = gray.begin(); it != gray.end(); it++) {
    //         if(*it == c) {
    //             gray.erase(it);
    //             break;
    //         }
    //     }
    // }

    for(auto c : gray)
        std::cout << c << " ";
    std::cout << "\n";
    
    for(auto &[c, d] : yellow)
        std::cout << c << " " << d << " ";
    std::cout << "\n";

    
    for(auto &[c, d] : green)
        std::cout << c << " " << d << " ";
    std::cout << "\n";


    //std::cout << "done patterning\n";
    updateTrieHelper(trie.getRoot(), 0, gray, yellow, green);
    //std::cout << "done updating\n";
    // cut down 0-children parents


}

void Game::Wort::updateTrie(std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green) {
    updateTrieHelper(trie.getRoot(), 0, gray, yellow, green);
}

void Game::Wort::updateTrieHelper(TrieNode *node, int depth, std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green) {    
    if(depth == 5) {
        // evaluate
        return;
    }

    std::vector<char> localGray;
    std::vector<char> localYellow;
    std::vector<char> localGreen;

    for(auto &[c, d] : green) {
        if(d == depth)
            localGreen.push_back(c);
    }

    for(auto &[c, d] : yellow)
        if(d == depth)
            localYellow.push_back(c);

    if(localGreen.size() == 0) {
        for(auto &[c, d] : yellow)
            if(d == depth)
                localGray.push_back(c);

        for(auto c : gray)
           localGray.push_back(c);
    }

    for(auto c : localGreen)
        for(int i = 0; i < 26; i++) {
            if(node->children[i] == NULL || node->children[i]->c == c)
                continue;
            
            delete node->children[i];
            node->children[i] = NULL;
            node->nrChildren--;
        }
    
    for(auto c : localGray) {
        if(node->children[c - 'a'] == NULL)
            continue;

        delete node->children[c - 'a'];
        node->children[c - 'a'] = NULL;
        node->nrChildren--;
    }

    for(auto n : node->children) {
        if(n != NULL)
            updateTrieHelper(n, depth + 1, gray, yellow, green);
    }

    for(int i = 0; i < 26; i++) {
        if(node->children[i] == NULL)
            continue;
        if(node->children[i]->nrChildren == 0 && !node->children[i]->isEnd) {
            delete node->children[i];
            node->children[i] = NULL;
            node->nrChildren--;
        }
    }
}

std::vector<std::string> Game::Wort::suggest() {
    std::vector<std::string> result;
    //std::cout << trie.getRoot()->nrChildren << ":";
    //trie.print();
    // for(auto c : trie.getRoot()->children) {
    //     if(c != NULL)
    //         std::cout << c->c << " ";
    // }
    //std::cout << "\n";
    for(auto _ = 0; _ < 3; _++) {
        //std::cout << "suggesting\n";
        std::string suggestion = trie.getRandom();
        result.push_back(suggestion);
    }

    return result;

}

// std::vector<std::string> Game::Wort::suggest() {
//     std::vector<std::string> result;
//     for(auto _ = 0; _ < 3; _++) {
//         std::string suggestion;
//         bool sw = suggestHelper(trie.getRoot(), 0, suggestion);
//         if(!sw)
//             break;
//         result.push_back(suggestion);
//     }
//     return result;
// }

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