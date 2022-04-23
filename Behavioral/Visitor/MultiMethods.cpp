#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeindex>

using namespace std;

struct GameObject;
void collide(const GameObject& first, const GameObject& second);

struct GameObject
{
    virtual ~GameObject()                         = default;
    [[nodiscard]] virtual type_index type() const = 0;

    virtual void collide(const GameObject& other) const { ::collide(*this, other); }
};

template<typename T>
struct GameObjectImpl : GameObject
{
    [[nodiscard]] type_index type() const override { return typeid(T); }
};

struct Planet : GameObjectImpl<Planet>
{};
struct Asteroid : GameObjectImpl<Asteroid>
{};
struct Spaceship : GameObjectImpl<Spaceship>
{};
struct ArmedSpaceship : Spaceship
{
    [[nodiscard]] type_index type() const override
    {
        return typeid(ArmedSpaceship); // required for collision to function
    }
}; // model limitation

void spaceship_planet()
{
    cout << "spaceship lands on planet\n";
}
void asteroid_planet()
{
    cout << "asteroid burns up in atmosphere\n";
}
void asteroid_spaceship()
{
    cout << "asteroid hits and destroys spaceship\n";
}
void asteroid_armed_spaceship()
{
    cout << "spaceship shoots asteroid\n";
}

std::map<std::pair<type_index, type_index>, std::function<void(void)>> outcomes{
  {{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
  {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
  {{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship},
  {{typeid(Asteroid), typeid(ArmedSpaceship)}, asteroid_armed_spaceship}};

void collide(const GameObject& first, const GameObject& second)
{
    auto it = outcomes.find({first.type(), second.type()});
    if (it == outcomes.end()) {
        it = outcomes.find({second.type(), first.type()});
        if (it == outcomes.end()) {
            cout << "objects pass each other harmlessly\n";
            return;
        }
    }
    it->second();
}

int main()
{
    ArmedSpaceship spaceship;
    Asteroid       asteroid;
    Planet         planet;

    collide(planet, spaceship);
    collide(planet, asteroid);
    collide(spaceship, asteroid);
    collide(planet, planet);

    cout << "Member collision:\n";
    planet.collide(asteroid);

    // but this won't work
    spaceship.collide(planet);

    return 0;
}
