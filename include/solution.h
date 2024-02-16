#include <vector>
#include <string>

class Solution {
    public:
        Solution();
        ~Solution() = default;
        bool guess(std::string guess);
        std::string getPattern();
        void setWord(std::string word);

    private:
        std::string word;
        std::string pattern;
        std::vector<int8_t> matchingLetters;

};