#include <iostream>
#include <string>
using namespace std;

class Game
{
public:
    explicit Game(int numberOfPlayers)
        : numberOfPlayers_(numberOfPlayers)
    {}

    virtual ~Game() = default;

    // Note: This is the template pattern function which calls a pure virtual function start(), have_winner() etc.
    void run()
    {
        start();
        while (!have_winner()) {
            take_turn();
        }
        cout << "Player " << get_winner() << " wins.\n";
    }

protected:
    virtual void start()       = 0;
    virtual bool have_winner() = 0;
    virtual void take_turn()   = 0;
    virtual int  get_winner()  = 0;

    int currentPlayer_{0};
    int numberOfPlayers_;
};

// Note : The rules of getting a winner is not important here. It's just a dummy example
class Chess : public Game
{
public:
    explicit Chess()
        : Game{2}
    {}

protected:
    void start() override { cout << "Starting a game of chess with " << numberOfPlayers_ << " players\n"; }

    bool have_winner() override { return turns == max_turns; }

    void take_turn() override
    {
        cout << "Turn " << turns << " taken by player " << currentPlayer_ << "\n";
        turns++;
        currentPlayer_ = (currentPlayer_ + 1) % numberOfPlayers_;
    }

    int get_winner() override { return currentPlayer_; }

private:
    int turns{0}, max_turns{10};
};

int main()
{
    Chess chess;
    chess.run();

    getchar();
    return 0;
}
