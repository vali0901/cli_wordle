#include <vector>
#include <string>

class Solution {
    public:
    Solution();
    ~Solution();
    bool guess(std::string guess);
    std::string getPattern();
    void setWord(std::string word);
    std::vector<std::vector<char>> getPool();

    private:
    std::vector<std::vector<char>> pool;
    std::string word;
    std::string pattern;
    std::vector<int8_t> matchingLetters;
    
};