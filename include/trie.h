#include <string>

class TrieNode{
    public:
        TrieNode(bool, char);
        ~TrieNode();

        bool isEnd;
        char c;
        int nrChildren;
        TrieNode* children[26];
};

class Trie{
    public:
        Trie();
        ~Trie();
        TrieNode* getRoot();
        void insert(std::string word);
        bool find(std::string word);
        std::string getRandom();

        void print();
    
        void operator=(const Trie &other);
    
    private:
        TrieNode* root;
        void getRandomHelper(TrieNode* currNode, int depth, std::string &result);
        void printHelper(TrieNode* currNode, std::string &word, int depth);
        void copyHelper(TrieNode* currNode, TrieNode* otherNode);
};
