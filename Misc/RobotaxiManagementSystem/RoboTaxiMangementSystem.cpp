// Problem
//
//     Company DoWeCheatThemAndHow LLC would like to revolutionize the taxi
//         dispatching industry and wants to create a new dispatching
//         software.The
//             dispatching software must keep accurate track of the taxi fleet,
//     their location, activity,
//     and passenger manifest(including location of the passengers, travel time,
//                            and wait time)
//             .
//
//         For the “passenger requests a ride” use case:
//
// Passenger makes a request for a ride by calling the dispatcher and requests a
// ride, providing their current location and desired destination. Dispatcher
// enters the information into the Software The first available taxi is assigned
// the job to pick up and deliver the passenger The assigned taxi’s location is
// monitored throughout the entire job, in route to pick up, pick up, in route
// to drop-off, and drop-off.
//
//
// Using any method you are most comfortable with (whiteboard, PowerPoint, code,
// back of a napkin, etc.) present how you would approach solving this problem.

// SOLID Principles
// Single Responsibility Principle
// Open/Closed Principle
// Liskov Substitution Principle
// Interface Segregation Principle
// Dependency Inversion Principle

// Primary Actor - Passenger
// Secondary Actor - Taxi
// System - DispathSystem

#include <string>
#include <vector>

using ID = int;

struct Position {
  double latitude;
  double longitude;
};

struct Location {
  Position position;
  std::string name;
};

enum class TaxiStatus : uint8_t {
  kIdle,
  kAtPickup,
  kInRouteToPickUp,
  kInRouteToDropOff,
  kAtDropOff
};

// Dependency Inversion Principle
class Taxi {
public:
  [[nodiscard]] virtual void driveToPickUp(const Location &location) const = 0;
  [[nodiscard]] virtual void driveToDropOff(const Location &location) const = 0;
};

class EconomyTaxi : public Taxi {
public:
  EconomyTaxi(ID id, TaxiStatus status) : id_(id), status_(status){};
  ~EconomyTaxi() = default;

  void driveToPickUp(const Location &location) const override {
    // Send command to vehicle control system to drive to pick up location
  }

  void driveToDropoff(const Location &location) const override {
    // Send command to vehicle control system to drive to pick up location
  }

private:
  bool updatePosition(Position newPosition) {
    currentPosition_ = newPosition;
    return true;
  }

  ID id_;
  Position currentPosition_;
  TaxiStatus status_;
};

class Passenger {
public:
  Passenger(int id, std::string &&name) : id_(id), name_(std::move(name)){};

private:
  ID id_;
  std::string name_;
  Position currentPosition_;
  Location pickupLocation_;
  Location dropoffLocation_;
};

class DispatchSystem final {
public:
  DispatchSystem(std::vector<Taxi> &&taxis, std::vector<Passenger> &&passengers)
      : taxis_(std::move(taxis)), passengers_(std::move(passengers)){};

private:
  std::vector<Taxi> taxis_;
  std::vector<Passenger> passengers_;
};

int main() { return 0; }