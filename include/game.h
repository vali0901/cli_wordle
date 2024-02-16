#include "../include/trie.h"
#include "../include/solution.h"
#include <string>


class Game{
    public:
    static Game *getInstance();
    static void removeInstance();
    void populateTrie(std::string filename);
    void testTrie();
    void startGame();

    private:
        class Wort {
            public:
                Wort(Trie &trie, Solution &sol);
                std::vector<std::string> suggest();
                void updateTrie(std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green);
                void guess(std::string guess, std::string pattern);
                void init(Trie &trie);
            private:
                Trie trie;
                Solution &sol;
                bool suggestHelper(TrieNode *node, int depth, std::string &result);
                void updateTrieHelper(TrieNode *node, int depth, std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green);

        };

        static Game *instance;
        int test;
        Trie trie;
        Solution sol;
        Wort *wort;

        Game();
        Game(const Game &other) = delete;
        Game &operator=(const Game &other) = delete;
        ~Game();


    
};