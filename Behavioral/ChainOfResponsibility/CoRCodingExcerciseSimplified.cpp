#include <iostream>
#include <vector>

#include <gtest/gtest.h>

using namespace std;
struct Creature;
struct Game
{
    vector<Creature*> creatures;
};

struct StatQuery
{
    enum Statistic
    {
        attack,
        defense
    } statistic;
    int result;
};

struct Creature
{
protected:
    Game& game_;
    int   base_attack, base_defense;

public:
    Creature(Game& game, int base_attack, int base_defense)
        : game_(game)
        , base_attack(base_attack)
        , base_defense(base_defense)
    {}
    virtual ~Creature() = default;

    virtual int  get_attack()                                  = 0;
    virtual int  get_defense()                                 = 0;
    virtual void query(StatQuery& statQuery)                   = 0;
};

class Goblin : public Creature
{
public:
    Goblin(Game& game, int base_attack, int base_defense)
        : Creature(game, base_attack, base_defense)
    {}

    explicit Goblin(Game& game)
        : Creature(game, 1, 1)
    {}

    int get_attack() override
    {
        StatQuery queryStat{StatQuery::Statistic::attack, base_attack};
        getStatistics(queryStat);

        return queryStat.result;
    }

    int get_defense() override
    {
        StatQuery queryStat{StatQuery::Statistic::defense, base_defense};
        getStatistics(queryStat);

        return queryStat.result;
    }

    void query(StatQuery& statQuery) override
    {
        switch (statQuery.statistic) {
            case StatQuery::Statistic::attack:
                break;
            case StatQuery::Statistic::defense:
                statQuery.result += 1;
                break;
        }
    }

private:
    void getStatistics(StatQuery& queryStat) {
        for (auto& creature : game_.creatures) {
            if (creature != (Creature*)this) {
                creature->query(queryStat);
            }
        }
    }

};

class GoblinKing : public Goblin
{
public:
    explicit GoblinKing(Game& game)
        : Goblin(game, 3, 3)
    {}

    void query(StatQuery& queryStat) override
    {
        queryStat.result += 1;
    }
};

namespace {
class Evaluate : public testing::Test
{
public:
};

TEST_F(Evaluate, ManyGoblinsTest)
{
    Game   game;
    Goblin goblin{game};
    game.creatures.push_back(&goblin);

    cout << "Checking that a baseline goblin is a 1/1...\n";

    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(1, goblin.get_defense());

    cout << "Adding a second goblin, now they should be 1/2...\n";
    Goblin goblin2{game};
    game.creatures.push_back(&goblin2);

    ASSERT_EQ(1, goblin.get_attack());
    ASSERT_EQ(2, goblin.get_defense());

    cout << "Adding a goblin king, now a goblin should be 2/3...\n";
    GoblinKing goblin3{game};
    game.creatures.push_back(&goblin3);

    ASSERT_EQ(2, goblin.get_attack());
    ASSERT_EQ(3, goblin.get_defense());
}

} // namespace

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}
