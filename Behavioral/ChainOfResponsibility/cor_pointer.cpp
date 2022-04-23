#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <fmt/format.h>

using namespace std;

struct Creature
{
    string name_;
    int    attack_, defense_;

    Creature(string name, const int attack, const int defense)
        : name_(std::move(name))
        , attack_(attack)
        , defense_(defense)
    {}

    friend ostream& operator<<(ostream& os, const Creature& obj)
    {
        return os << "name: " << obj.name_ << " attack_: " << obj.attack_ << " defense_: " << obj.defense_;
    }
};

class CreatureModifier
{
private:
    std::unique_ptr<CreatureModifier> next_{nullptr}; // unique_ptr

protected:
    Creature& creature_; // pointer or shared_ptr

public:
    explicit CreatureModifier(Creature& creature)
        : creature_(creature)
    {}
    virtual ~CreatureModifier() = default;

    void add(std::unique_ptr<CreatureModifier> cm)
    {
        if (next_ != nullptr) {
            next_->add(std::move(cm));
        } else {
            next_ = std::move(cm);
        }
    }

    // two approaches:

    // 1. Always call base handle(). There could be additional logic here.
    // 2. Only call base handle() when you cannot handle things yourself.

    virtual void handle()
    {
        fmt::print("Base handle. Attack : {} Defense : {} \n", creature_.attack_, creature_.defense_);
        if (next_) {
            next_->handle();
        }
    }
};

// 1. Double the creature's attack_
// 2. Increase defense by 1 unless power > 2
// 3. No bonuses can be applied to this creature

class NoBonusesModifier : public CreatureModifier
{
public:
    explicit NoBonusesModifier(Creature& creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        // nothing
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    explicit DoubleAttackModifier(Creature& creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        fmt::print("Double attack handle \n");
        creature_.attack_ *= 2;
        CreatureModifier::handle();
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    explicit IncreaseDefenseModifier(Creature& creature)
        : CreatureModifier(creature)
    {}

    void handle() override
    {
        if (creature_.attack_ <= 2) {
            fmt::print("Increase defense handle \n");
            creature_.defense_ += 1;
        }
        CreatureModifier::handle();
    }
};

int main()
{
    Creature goblin{"Goblin", 1, 1};
    auto     rootPtr = std::make_unique<CreatureModifier>(goblin);
    auto     r1Ptr   = std::make_unique<DoubleAttackModifier>(goblin);
    auto     r1_2Ptr = std::make_unique<DoubleAttackModifier>(goblin);
    auto     r2Ptr   = std::make_unique<IncreaseDefenseModifier>(goblin);
    //    NoBonusesModifier nb{goblin}; // effectively Command objects

    // root.add(&nb);
    rootPtr->add(std::move(r1Ptr));
    rootPtr->add(std::move(r1_2Ptr));
    rootPtr->add(std::move(r2Ptr));

    rootPtr->handle(); // annoying

    cout << goblin << endl;

    return 0;
}
