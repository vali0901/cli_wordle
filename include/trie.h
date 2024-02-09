#include <string>

class TrieNode{
    public:
        TrieNode(bool, char);
        ~TrieNode();

        bool isEnd;
        char c;
        TrieNode* children[26];
};

class Trie{
    public:
    Trie();
    ~Trie();
    void insert(std::string word);
    bool find(std::string word);
    void print();
    std::string getRandom();
    TrieNode* getRoot();
    
    private:
    void getRandomHelper(TrieNode* currNode, int depth, std::string &result);
    void printHelper(TrieNode* currNode, std::string &word);
    TrieNode* root;
};
