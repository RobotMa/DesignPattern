#include <algorithm>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

// Note that this is not a observer question. An observer pattern allows a receiver to dynamically subscribe/unsubscribe
// from receiving requests
using namespace std;

struct IRat
{
    // Note : there a difference between increase/decrease attack when a rat enters/dies
    virtual void ratEnters(IRat* sender) = 0;
    virtual void ratDies()               = 0;
    virtual void notify(IRat* target)    = 0;
    virtual ~IRat()                      = default;
};

struct Game
{
    vector<IRat*> rats_;
    void          fireRatEnters(IRat* sender)
    {
        for (auto rat : rats_) {
            rat->ratEnters(sender);
        }
    }

    void fireRatDies()
    {
        for (auto rat : rats_) {
            rat->ratDies();
        }
    }

    void fireNotify(IRat* target)
    {
        for (auto rat : rats_) {
            rat->notify(target);
        }
    }
};

struct Rat : IRat
{
    Game& game_;
    int   attack{1};

    explicit Rat(Game& game)
        : game_(game)
    {
        game.rats_.push_back(this);
        game.fireRatEnters(this);
    }

    ~Rat() override
    {
        game_.fireRatDies();
        game_.rats_.erase(std::remove(game_.rats_.begin(), game_.rats_.end(), this));
    }

    void ratEnters(IRat* sender) override
    {
        if (sender != this) {
            ++attack;
            game_.fireNotify(sender);
        }
    }

    void ratDies() override { --attack; }

    void notify(IRat* target) override
    {
        if (target == this) {
            ++attack;
        }
    }
};

namespace {

class Evaluate : public ::testing::Test
{};

TEST_F(Evaluate, SingleRatTest)
{
    Game game;
    Rat  rat{game};
    ASSERT_EQ(1, rat.attack);
}

TEST_F(Evaluate, TwoRatTest)
{
    Game game;
    Rat  rat{game};
    Rat  rat2{game};
    ASSERT_EQ(2, rat.attack);
    ASSERT_EQ(2, rat2.attack);
}

TEST_F(Evaluate, ThreeRatsOneDies)
{
    Game game;
    Rat  rat{game};
    ASSERT_EQ(1, rat.attack);

    Rat rat2{game};
    ASSERT_EQ(2, rat.attack);
    ASSERT_EQ(2, rat2.attack);

    {
        Rat rat3{game};

        ASSERT_EQ(3, rat.attack);
        ASSERT_EQ(3, rat2.attack);
        ASSERT_EQ(3, rat3.attack);
    }

    ASSERT_EQ(2, rat.attack);
    ASSERT_EQ(2, rat2.attack);
}

} // namespace

int main(int ac, char* av[])
{
    //::testing::GTEST_FLAG(catch_exceptions) = false;
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}