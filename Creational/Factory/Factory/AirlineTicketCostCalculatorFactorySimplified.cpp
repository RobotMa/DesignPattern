#include <iostream>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

enum class SeatClass : uint8_t { Economy, Premium, Business };

class AbstractAirline {
public:
  virtual double calOperationCost() const = 0;
  virtual double calAirlinePrice() const = 0;
  virtual ~AbstractAirline() = default;
};

class Airline : public AbstractAirline {
public:
  Airline(double distance, SeatClass seatClass)
      : distance_(distance), seatClass_(seatClass) {}

  virtual double calOperationCost() const override {

    if (seatClass_ == SeatClass::Economy) {
      return 0.0;
    }

    if (seatClass_ == SeatClass::Premium) {
      return 25.0;
    }

    if (seatClass_ == SeatClass::Business) {
      return 50.0 + 0.25 * distance_;
    }
  }

  virtual double calAirlinePrice() const override { return calOperationCost(); }

protected:
  double distance_;
  SeatClass seatClass_;
};

class Delta : public Airline {
public:
  Delta(double distance, SeatClass seatClass) : Airline(distance, seatClass) {}

  double calAirlinePrice() const override {

    return calOperationCost() + distanceCharge_ * distance_;
  }

private:
  double distanceCharge_{0.5};
};

class United : public Airline {
public:
  United(double distance, SeatClass seatClass) : Airline(distance, seatClass) {}

  double calAirlinePrice() const override {

    double oCost = calOperationCost();

    oCost += distanceCharge_ * distance_;

    if (seatClass_ == SeatClass::Premium) {
      oCost += 0.1 * distance_;
    }

    return oCost;
  }

private:
  double distanceCharge_{0.75};
};

class Southwest : public Airline {

public:
  Southwest(double distance, SeatClass seatClass)
      : Airline(distance, seatClass) {}

  double calAirlinePrice() const override {
    return distanceCharge_ * distance_;
  }

private:
  double distanceCharge_{1.0};
};

class LuigiAir : public Airline {

public:
  LuigiAir(double distance, SeatClass seatClass)
      : Airline(distance, seatClass) {}

  double calAirlinePrice() const override {
    return std::max(100.0, 2 * calOperationCost());
  }
};

std::unique_ptr<AbstractAirline> makeAirline(const std::string &input) {

  std::unordered_map<std::string, SeatClass> seatClassMap{
      {"Economy", SeatClass::Economy},
      {"Premium", SeatClass::Premium},
      {"Business", SeatClass::Business}};

  std::istringstream ss(input);

  std::string airline;
  double miles;
  std::string seatClass;

  ss >> airline >> miles >> seatClass;

  if (airline == "Delta") {
    return std::make_unique<Delta>(miles, seatClassMap[seatClass]);
  }

  if (airline == "United") {
    return std::make_unique<United>(miles, seatClassMap[seatClass]);
  }

  if (airline == "Southwest") {
    return std::make_unique<Southwest>(miles, seatClassMap[seatClass]);
  }

  if (airline == "LuigiAir") {
    return std::make_unique<LuigiAir>(miles, seatClassMap[seatClass]);
  }
}

int main() {

  const std::vector<std::string> airlines{
      "United 150.0 Premium", "Delta 60.0 Business", "Southwest 1000.0 Economy",
      "LuigiAir 50.0 Business"};

  for (const auto &airline : airlines) {
    auto airlineTicket = makeAirline(airline);
    std::cout << "Airline: " << airline
              << " Price: " << airlineTicket->calAirlinePrice() << '\n';
  }

  return 0;
}