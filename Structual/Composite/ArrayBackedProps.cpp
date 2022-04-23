#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>

class Creature
{
    enum class Abilities : uint8_t
    {
        str,
        agl,
        intl,
        count
    };
    std::array<int, static_cast<int>(Abilities::count)> abilities;

public:
    [[nodiscard]] int get_strength() const { return abilities[static_cast<int>(Abilities::str)]; }
    void              set_strength(int value) { abilities[static_cast<int>(Abilities::str)] = value; }

    [[nodiscard]] int get_agility() const { return abilities[static_cast<int>(Abilities::agl)]; }
    void              set_agility(int value) { abilities[static_cast<int>(Abilities::agl)] = value; }

    [[nodiscard]] int get_intelligence() const { return abilities[static_cast<int>(Abilities::intl)]; }
    void              set_intelligence(int value) { abilities[static_cast<int>(Abilities::intl)] = value; }

    [[nodiscard]] int sum() const { return std::accumulate(abilities.begin(), abilities.end(), 0); }

    [[nodiscard]] double average() const { return sum() / static_cast<double>(Abilities::count); }

    [[nodiscard]] int max() const { return *std::max_element(abilities.begin(), abilities.end()); }
};

int main()
{
    Creature orc{};
    orc.set_strength(16);
    std::cout << "Strength : " << orc.get_strength() << '\n';
    orc.set_agility(11);
    orc.set_intelligence(9);

    std::cout << "The orc has an average stat of " << orc.average() << " and a maximum stat of " << orc.max() << "\n";

    return 0;
}