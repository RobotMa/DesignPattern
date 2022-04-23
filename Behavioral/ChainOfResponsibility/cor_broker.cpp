#include <iostream>
#include <string>
#include <utility>

#include <boost/signals2.hpp>

using namespace std;

struct Query
{
    string creatureName_;
    enum Argument
    {
        attack,
        defense
    } argument_;
    int result_;

    Query(string creature_name, const Argument argument, const int result)
        : creatureName_(std::move(creature_name))
        , argument_(argument)
        , result_(result)
    {}
};

struct Game // TODO : mediator (how is this close to a real mediator?
{
    boost::signals2::signal<void(Query&)> queries;
};

class Creature
{
private:
    Game& game_;
    int   attack_, defense_;

public:
    string name_;
    Creature(Game& game, string name, const int attack, const int defense)
        : game_(game)
        , attack_(attack)
        , defense_(defense)
        , name_(std::move(name))
    {}

    [[nodiscard]] int getAttack() const
    {
        Query q{name_, Query::Argument::attack, attack_};
        game_.queries(q);
        return q.result_;
    }

    [[nodiscard]] int getDefense() const
    {
        Query q{name_, Query::Argument::defense, defense_};
        game_.queries(q);
        return q.result_;
    }

    friend ostream& operator<<(ostream& os, const Creature& obj)
    {
        return os << "name: " << obj.name_ << " attack_: " << obj.getAttack() // note here
                  << " defense_: " << obj.getDefense();
    }
};

class CreatureModifier
{
private:
    Game&     game_;
    Creature& creature_;

public:
    CreatureModifier(Game& game, Creature& creature)
        : game_(game)
        , creature_(creature)
    {}
    virtual ~CreatureModifier() = default;

    // there is no handle() function
};

class DoubleAttackModifier : public CreatureModifier
{
private:
    boost::signals2::connection conn;

public:
    DoubleAttackModifier(Game& game, Creature& creature)
        : CreatureModifier(game, creature)
    {
        // whenever someone wants this creature's attack_,
        // we return DOUBLE the value_
        conn = game.queries.connect([&creature](Query& q) {
            if (q.creatureName_ == creature.name_ && q.argument_ == Query::Argument::attack)
                q.result_ *= 2;
        });
    }

    ~DoubleAttackModifier() override { conn.disconnect(); }
};

class DoubleDefenseModifier : public CreatureModifier
{
private:
    boost::signals2::connection conn;

public:
    DoubleDefenseModifier(Game& game, Creature& creature)
        : CreatureModifier(game, creature)
    {
        // whenever someone wants this creature's attack_,
        // we return DOUBLE the value_
        conn = game.queries.connect([&creature](Query& q) {
            if (q.creatureName_ == creature.name_ && q.argument_ == Query::Argument::defense)
                q.result_ *= 2;
        });
    }

    ~DoubleDefenseModifier() override { conn.disconnect(); }
};

// similar idea, but Query instead of Command
int main()
{
    Game     game;
    Creature goblin{game, "Strong Goblin", 2, 2};

    cout << goblin << endl;

    DoubleAttackModifier dam{game, goblin};
    cout << goblin << endl;

    DoubleDefenseModifier def{game, goblin};
    cout << goblin << endl;

    getchar();
    return 0;
}
