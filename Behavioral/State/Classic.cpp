#include <iostream>
#include <string>
using namespace std;

class LightSwitch;

struct State
{
    virtual void on(LightSwitch* ls)
    {
        (void)ls;
        cout << "Light is already on\n";
    }
    virtual void off(LightSwitch* ls)
    {
        (void)ls;
        cout << "Light is already off\n";
    }
    virtual ~State() = default;
};

struct OnState : State
{
    OnState() { cout << "Light turned on\n"; }

    void off(LightSwitch* ls) override;
};

struct OffState : State
{
    OffState() { cout << "Light turned off\n"; }

    void on(LightSwitch* ls) override;
};

class LightSwitch
{
    State* state_;

public:
    LightSwitch() { state_ = new OffState(); }
    void set_state(State* state) { this->state_ = state; }
    void on() { state_->on(this); }
    void off() { state_->off(this); }
};

void OnState::off(LightSwitch* ls)
{
    cout << "Switching light off...\n";
    ls->set_state(new OffState());
    delete this;
}

void OffState::on(LightSwitch* ls)
{
    cout << "Switching light on...\n";
    ls->set_state(new OnState());
    delete this;
}

int main()
{
    LightSwitch ls;
    ls.on();
    ls.off();
    ls.off();
    getchar();
}