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
    int   baseAttack_, baseDefense_;

public:
    Creature(Game& game, int base_attack, int base_defense)
        : game_(game)
        , baseAttack_(base_attack)
        , baseDefense_(base_defense)
    {}

    virtual ~Creature()                                                    = default;
    [[nodiscard]] virtual int get_attack() const                           = 0;
    [[nodiscard]] virtual int get_defense() const                          = 0;
    virtual void              query(Creature* source, StatQuery& sq) const = 0;
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

    [[nodiscard]] int get_attack() const override { return get_statistic(StatQuery::attack); }

    [[nodiscard]] int get_defense() const override { return get_statistic(StatQuery::defense); }

    void query(Creature* source, StatQuery& sq) const override
    {
        if (source == this) {
            switch (sq.statistic) {
                case StatQuery::attack:
                    sq.result += baseAttack_;
                    break;
                case StatQuery::defense:
                    sq.result += baseDefense_;
                    break;
            }
        } else {
            if (sq.statistic == StatQuery::defense) {
                sq.result++;
            }
        }
    }

private:
    [[nodiscard]] int get_statistic(StatQuery::Statistic stat) const
    {
        StatQuery q{stat, 0};
        for (auto c : game_.creatures) {
            //            c->query((Creature*)this, q);
            c->query((Creature*)this, q);
        }
        return q.result;
    }
};

class GoblinKing : public Goblin
{
public:
    explicit GoblinKing(Game& game)
        : Goblin(game, 3, 3)
    {}

private:
    void query(Creature* source, StatQuery& sq) const override
    {
        if (source != this && sq.statistic == StatQuery::attack) {
            sq.result++;
        } else {
            Goblin::query(source, sq);
        }
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