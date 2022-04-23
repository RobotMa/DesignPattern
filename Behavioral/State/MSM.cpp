#include <iostream>
#include <string>
#include <vector>

// back-end
#include <boost/msm/back/state_machine.hpp>

// front-end
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;
using namespace std;

vector<string> state_names{"off hook"s, "connecting"s, "connected"s, "on hold"s, "destroyed"s};

// transitions/events
struct CallDialed
{};
struct HungUp
{};
struct CallConnected
{};
struct PlacedOnHold
{};
struct TakenOffHold
{};
struct LeftMessage
{};
struct PhoneThrownIntoWall
{};

struct PhoneStateMachine : msm::front::state_machine_def<PhoneStateMachine>
{
    bool angry{true}; // start with false

    struct OffHook : msm::front::state<>
    {};
    struct Connecting : msm::front::state<>
    {
        template<class Event, class FSM>
        void on_entry(Event const& evt, FSM&)
        {
            cout << "We are connecting..." << endl;
        }
        // also on_exit
    };
    struct Connected : msm::front::state<>
    {};
    struct OnHold : msm::front::state<>
    {};
    struct PhoneDestroyed : msm::front::state<>
    {};

    struct PhoneBeingDestroyed
    {
        template<class EVT, class FSM, class SourceState, class TargetState>
        void operator()(EVT const&, FSM&, SourceState&, TargetState&)
        {
            cout << "Phone breaks into a million pieces" << endl;
        }
    };

    struct CanDestroyPhone
    {
        template<class EVT, class FSM, class SourceState, class TargetState>
        bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
        {
            return fsm.angry;
        }
    };

    // start, event, target, action_, guard
    struct transition_table
        : boost::mpl::vector<
            msm::front::Row<OffHook, CallDialed, Connecting>, msm::front::Row<Connecting, CallConnected, Connected>,
            msm::front::Row<Connected, PlacedOnHold, OnHold>,
            msm::front::Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>>
    {};

    // starting state_
    using initial_state = OffHook;

    // what happens if there's nowhere to go
    template<class FSM, class Event>
    void no_transition(Event const& e, FSM&, size_t state)
    {
        cout << "No transition from state " << state_names[state] << " on event " << typeid(e).name() << endl;
    }
};

int main()
{
    msm::back::state_machine<PhoneStateMachine> phone;

    auto info = [&phone]() {
        const auto state = phone.current_state()[0];
        cout << "The phone is currently " << state_names[static_cast<size_t>(state)] << "\n";
    };

    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(PhoneThrownIntoWall{});
    info();

    // try process_event here :)
    phone.process_event(CallDialed{});

    cout << "We are done using the phone"
         << "\n";

    getchar();
    return 0;
}
