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
    void insert(std::string word);
    bool find(std::string word);
    void print();
    std::string getRandom();
    TrieNode* getRoot();
    int count();
    void remove(TrieNode* currNode);

    void operator=(const Trie &other);

    
    private:
    void getRandomHelper(TrieNode* currNode, int depth, std::string &result);
    void printHelper(TrieNode* currNode, std::string &word, int depth);
    void countHelper(TrieNode* currNode, int &counter);
    void copyHelper(TrieNode* currNode, TrieNode* otherNode);
    TrieNode* root;
};
