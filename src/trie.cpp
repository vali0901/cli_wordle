#include "../include/trie.h"
#include <iostream>
#include <string.h>

TrieNode::TrieNode(bool state = false, char c = '\0') {
    this->isEnd = state;
    this->c = c;
    memset(children, 0, 26 * sizeof(TrieNode *));
    this->nrChildren = 0;
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 26; i++) {
        if (this->children[i] != NULL) {
            delete this->children[i];
        }
    }
}

Trie::Trie() {
    this->root = new TrieNode();
}

Trie::~Trie() {
    delete this->root;
}

TrieNode* Trie::getRoot() {
    return this->root;
}

void Trie::insert(std::string word) {
    TrieNode* node = this->root;
    for (auto &c : word) {
        if (node->children[c - 'a'] == NULL) {
            node->children[c - 'a'] = new TrieNode(false, c);
            node->nrChildren++;
        }
        node = node->children[c - 'a'];
    }
    node->isEnd = true;
}

bool Trie::find(std::string word) {
    TrieNode* node = this->root;
    for (auto &c : word) {
        if (node->children[c - 'a'] == NULL) {
            return false;
        }
        node = node->children[c - 'a'];
    }
    
    return node->isEnd;
}

std::string Trie::getRandom() {
    std::string result = "";
    this->getRandomHelper(this->root, 0, result);
    return result;
}

void Trie::getRandomHelper(TrieNode* currNode, int depth, std::string &result) {
    if(depth == 5 && currNode->isEnd)
        return;

    int index;
    do {
        index = rand() % 26;
    } while(currNode->children[index] == NULL);

    result += currNode->children[index]->c;
    getRandomHelper(currNode->children[index], depth + 1, result);
}

void Trie::print() {
    std::string word = "";
    printHelper(this->root, word, 0);
}

void Trie::printHelper(TrieNode* currNode, std::string &word, int depth = 0) {
    // if (currNode->isEnd) {
    //     std::cout << word << "\n";
    // }
    for(auto _ = 0; _ < depth; _++)
        std::cout << ' ';   
    std::cout << currNode->c << " " << currNode->nrChildren << "\n";

    for (int i = 0; i < 26; i++) {
        if (currNode->children[i] != NULL) {
            word += currNode->children[i]->c;
            printHelper(currNode->children[i], word, depth + 1);
            word.pop_back();
        }
    }
}

void Trie::operator=(const Trie &other) {
    copyHelper(this->root, other.root);
}

void Trie::copyHelper(TrieNode* currNode, TrieNode* otherNode) {
    currNode->isEnd = otherNode->isEnd;
    currNode->c = otherNode->c;
    currNode->nrChildren = otherNode->nrChildren;
    for (int i = 0; i < 26; i++) {
        if (otherNode->children[i] != NULL) {
            currNode->children[i] = new TrieNode();
            copyHelper(currNode->children[i], otherNode->children[i]);
        } else {
            currNode->children[i] = NULL;
        }
    }
}