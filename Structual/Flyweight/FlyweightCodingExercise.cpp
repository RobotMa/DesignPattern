#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

using namespace std;

struct Sentence
{
    struct WordToken
    {
        bool capitalize;
    };

    vector<string>                   words_;
    unordered_map<size_t, WordToken> tokens_;

    explicit Sentence(const string& text)
    {
        istringstream iss{text};
        // TODO : remember to use this nice approach (istream_iterator) to get all the words_ in a string
        words_ = vector<string>(istream_iterator<string>{iss}, istream_iterator<string>{});
    }

    WordToken& operator[](size_t index)
    {
        tokens_[index] = WordToken{};
        return tokens_[index];
    }

    [[nodiscard]] string str() const
    {
        vector<string> ws;
        for (size_t i = 0; i < words_.size(); ++i) {
            string w = words_[i];
            auto   t = tokens_.find(i);
            if (t != tokens_.end() && t->second.capitalize) {
                transform(w.begin(), w.end(), w.begin(), ::toupper);
            }
            ws.push_back(w);
        }

        ostringstream oss;
        for (size_t i = 0; i < ws.size(); ++i) {
            oss << ws[i];
            if (i + 1 != ws.size())
                oss << " ";
        }
        return oss.str();
    }
};

namespace {
class Evaluate : public testing::Test
{
public:
};

TEST_F(Evaluate, BaselineTest)
{
    Sentence s{"alpha beta gamma"};
    s[0].capitalize = s[2].capitalize = false;
    s[1].capitalize                   = true;
    ASSERT_EQ("alpha BETA gamma", s.str());
}

} // namespace

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}