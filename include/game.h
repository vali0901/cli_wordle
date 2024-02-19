#include "../include/trie.h"
#include "../include/solution.h"
#include <string>


class Game{
    public:
    static Game *getInstance();
    static void removeInstance();
    void populateTrie(std::string filename);
    void startGame();

    private:
        static Game *instance;

        class Wort {
            public:
                Wort();
                ~Wort() = default;
                std::vector<std::string> suggest();
                void updateTrie(std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green);
                void guess(std::string guess, std::string pattern);
                void init(Trie &trie);
            private:
                enum class DiscoveryLevel {
                    NOT_DISCOVERED,
                    YELLOW,
                    DISCOVERED
                };

                Trie trie;
                std::vector<std::string> suggestions;
                float suggestionsScores[3];
                bool firstSuggestions;
                DiscoveryLevel charDiscoveryMap[26];
                float prices[26] = {/*a*/ 1.5, /*b*/ 1, /*c*/ 1, /*d*/ 1, /*e*/ 1.5,
                                    /*f*/ 0.75, /*g*/ 1, /*h*/ 1, /*i*/ 1.25, /*j*/ 0.5,
                                    /*k*/ 0.75, /*l*/ 1.25, /*m*/ 1, /*n*/ 1, /*o*/ 1.5,
                                    /*p*/ 1, /*q*/ 0.5, /*r*/ 1.25, /*s*/ 1.5, /*t*/ 1.25,
                                    /*u*/ 1, /*v*/ 0.75, /*w*/ 0.75, /*x*/ 0.5, /*y*/ 5,
                                    /*z*/ 0.5};

                void updateTrieHelper(TrieNode *node, int depth, std::string currWord, std::vector<char> gray, std::vector<std::pair<char, int>> yellow, std::vector<std::pair<char, int>> green);
                float computeScore(std::string word);
        };

        Trie trie;
        Solution sol;
        Wort *wort;

        bool match(std::string guess, std::string pattern);
        void gamemode1();
        void gamemode2();
        void gamemode3();

        Game();
        Game(const Game &other) = delete;
        Game &operator=(const Game &other) = delete;
        ~Game();    
};