#include <iostream>
#include <string>
#include <utility>

#include <boost/signals2.hpp>

struct EventData
{
    virtual ~EventData()       = default;
    virtual void print() const = 0;
};

struct PlayerScoredData : EventData
{
    std::string playerName;
    int         goalsScoredSoFar;

    PlayerScoredData(std::string player_name, const int goals_scored_so_far)
        : playerName(std::move(player_name))
        , goalsScoredSoFar(goals_scored_so_far)
    {}

    void print() const override
    {
        std::cout << playerName << " has scored! (their " << goalsScoredSoFar << " goal)"
                  << "\n";
    }
};

struct Game
{
    boost::signals2::signal<void(EventData*)> events; // observer
};

struct Player
{
    std::string name_;
    int         goals_scored = 0;
    Game&       game_;

    Player(std::string name, Game& game)
        : name_(std::move(name))
        , game_(game)
    {}

    void score()
    {
        goals_scored++;
        PlayerScoredData ps{name_, goals_scored};
        game_.events(&ps);
    }
};

struct Coach
{
    Game& game_;

    explicit Coach(Game& game)
        : game_(game)
    {
        // celebrate if player has scored <3 goals
        game_.events.connect([](EventData* e) {
            auto ps = dynamic_cast<PlayerScoredData*>(e);
            if (ps != nullptr && ps->goalsScoredSoFar < 3) {
                std::cout << "coach says: well done, " << ps->playerName << "\n";
            }
        });
    }
};

int main()
{
    Game   game;
    Player player{"Sam", game};
    Coach  coach{game};

    player.score();
    player.score();
    player.score(); // ignored by coach

    return 0;
}
