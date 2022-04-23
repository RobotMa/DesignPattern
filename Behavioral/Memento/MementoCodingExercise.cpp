#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include <gtest/gtest.h>

using namespace std;

struct Token
{
    int value_;

    explicit Token(int value)
        : value_(value)
    {}
};

struct Memento
{
    vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{
    vector<shared_ptr<Token>> tokens;

    Memento add_token(int value) { return add_token(make_shared<Token>(value)); }

    Memento add_token(const shared_ptr<Token>& token)
    {
        tokens.push_back(token);
        Memento m;
        m.tokens.reserve(tokens.size());
        std::transform(tokens.begin(), tokens.end(), std::back_inserter(m.tokens),
                       [](const auto& e) { return std::make_shared<Token>(e->value_); });
        return m;
    }

    void revert(const Memento& m)
    {
        tokens.clear();
        std::transform(m.tokens.begin(), m.tokens.end(), std::back_inserter(tokens),
                       [](const auto& token) { return std::make_shared<Token>(token->value_); });
    }
};

namespace {

class Evaluate : public ::testing::Test
{};

TEST_F(Evaluate, SingleTokenTest)
{
    TokenMachine tm;
    auto         m = tm.add_token(123);
    tm.add_token(456);
    tm.revert(m);
    ASSERT_EQ(1, tm.tokens.size());
    ASSERT_EQ(123, tm.tokens[0]->value_);
}

TEST_F(Evaluate, TwoTokenTest)
{
    TokenMachine tm;
    tm.add_token(1);
    auto m = tm.add_token(2);
    tm.add_token(3);
    tm.revert(m);
    ASSERT_EQ(2, tm.tokens.size());
    ASSERT_EQ(1, tm.tokens[0]->value_) << "First toke should have value 1, you got " << tm.tokens[0]->value_;
    ASSERT_EQ(2, tm.tokens[1]->value_);
}

TEST_F(Evaluate, FiddledTokenTest)
{
    TokenMachine tm;
    cout << "Made a token with value=111 and kept a reference\n";
    auto token = make_shared<Token>(111);
    cout << "Added this token to the list\n";
    tm.add_token(token);
    auto m = tm.add_token(222);
    cout << "Changed this token's value to 333 :)\n";
    token->value_ = 333;
    tm.revert(m);

    ASSERT_EQ(2, tm.tokens.size()) << "At this point, token machine should have exactly "
                                   << "two tokens_, you got " << tm.tokens.size();

    ASSERT_EQ(111, tm.tokens[0]->value_) << "You got the token value wrong here. "
                                         << "Hint: did you init the memento by-value?";
}

} // namespace

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}
