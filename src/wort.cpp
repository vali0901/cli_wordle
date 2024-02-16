#include "../include/game.h"
#include <string>
#include <iostream>
#include <string.h>


Game::Wort::Wort() {
    suggestions = std::vector<std::string>(3, "");
    firstSuggestions = true;
    for(auto &d : charDiscoveryMap)
        d = DiscoveryLevel::NOT_DISCOVERED;
}

void Game::Wort::init(Trie &trie) {
    this->trie = trie;
    suggestions = std::vector<std::string>(3, "");
    firstSuggestions = true;
    for(auto &d : charDiscoveryMap)
        d = DiscoveryLevel::NOT_DISCOVERED;
}

float Game::Wort::computeScore(std::string word) {
    float score = 0;
    int freqMap[26];

    memset(freqMap, 0, 26 * sizeof(int));
    
    for(auto &c : word) {
        freqMap[c - 'a']++;
        switch (charDiscoveryMap[c - 'a'])
        {
        case DiscoveryLevel::NOT_DISCOVERED:
            score += (freqMap[c - 'a'] == 1 ? 1 : 0) * prices[c - 'a'];
            break;
        case DiscoveryLevel::YELLOW:
            score += 5 / freqMap[c - 'a'] * prices[c - 'a'];
            break;

        default:
            break;
        }
    }
    return score;
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

            // if this letter is not yellow, mark it as discovered
            if(charDiscoveryMap[guess[i] - 'a'] != DiscoveryLevel::YELLOW)
                charDiscoveryMap[guess[i] - 'a'] = DiscoveryLevel::DISCOVERED;
        }
        else if(pattern[i] >= 'a' && pattern[i] <= 'z')  {
            yellow.push_back({guess[i], i});
            // if this letter has not been discovered yet (gray), mark it as yellow
            if(charDiscoveryMap[guess[i] - 'a'] != DiscoveryLevel::DISCOVERED)
                charDiscoveryMap[guess[i] - 'a'] = DiscoveryLevel::YELLOW;
        }
        else if(pattern[i] >= 'A' && pattern[i] <= 'Z') {
            green.push_back({guess[i], i});
        }
    }

    // init suggestions before updating them
    for(auto &s : suggestions)
        s = "";
    memset(suggestionsScores, 0, 3 * sizeof(float));

    updateTrieHelper(trie.getRoot(), 0, "", gray, yellow, green);
}

void Game::Wort::updateTrie(std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green) {
    updateTrieHelper(trie.getRoot(), 0, "", gray, yellow, green);
}

void Game::Wort::updateTrieHelper(TrieNode *node, int depth, std::string currWord, std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green) {    
    if(depth == 5) {
        // evaluate
        float score = computeScore(currWord);
        for(int i = 0; i < 3; i++) {
            if(score >= suggestionsScores[i]) {
                for(int j = 2; j > i; j--) {
                    suggestionsScores[j] = suggestionsScores[j - 1];
                    suggestions[j] = suggestions[j - 1];
                }
                suggestionsScores[i] = score;
                suggestions[i] = currWord;
                break;
            }
        }
        return;
    }

    // get letters for this depth
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

    // update trie
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

    // recursive call for children
    for(auto n : node->children)
        if(n != NULL)
            updateTrieHelper(n, depth + 1, currWord + n->c, gray, yellow, green);


    // cut 0-children nodes
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
    if(!firstSuggestions)
        return suggestions;

    firstSuggestions = false;
    for(auto i = 0; i < 3; i++)
        suggestions[i] = trie.getRandom();

    return suggestions;
}
