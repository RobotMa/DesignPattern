#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// enum for different ticket types
enum class TicketType : uint8_t { ECONOMY, BUSINESS, PREMIUM };

class AirlineCalculatorAbstract {
public:
  [[nodiscard]] virtual auto
  getOperationCost(double miles, TicketType ticketType) const -> double = 0;
  virtual ~AirlineCalculatorAbstract() = default;
};

// class for different airline calculators
class UnitedAirlineCalculator final : public AirlineCalculatorAbstract {
public:
  UnitedAirlineCalculator() = default;

  [[nodiscard]] auto getOperationCost(double miles, TicketType ticketType) const
      -> double override {

    double operationCost_usd{0.0};

    if (ticketType == TicketType::BUSINESS) {
      operationCost_usd = 50.0 + 0.25 * miles;
    } else if (ticketType == TicketType::PREMIUM) {
      operationCost_usd = 25.0;
    } else {
      operationCost_usd = 0.0;
    }

    double perAirlineCost_usd{0.0};
    perAirlineCost_usd = costPerMile_usd_ * miles;

    if (ticketType == TicketType::PREMIUM) {
      perAirlineCost_usd += 0.1 * miles;
    }

    return perAirlineCost_usd + operationCost_usd;
  }

private:
  const double costPerMile_usd_{0.75};

  friend class AirlineTicketCalculatorFactory;
};

class DeltaAirlineCalculator final : public AirlineCalculatorAbstract {
public:
  DeltaAirlineCalculator() = default;

  [[nodiscard]] auto getOperationCost(double miles, TicketType ticketType) const
      -> double override {

    double operationCost_usd{0.0};

    if (ticketType == TicketType::BUSINESS) {
      operationCost_usd = 50.0 + 0.25 * miles;
    } else if (ticketType == TicketType::PREMIUM) {
      operationCost_usd = 25.0;
    } else {
      operationCost_usd = 0.0;
    }

    double perAirlineCost_usd{0.0};
    perAirlineCost_usd = costPerMile_usd_ * miles;

    return perAirlineCost_usd + operationCost_usd;
  }

private:
  const double costPerMile_usd_{0.5};
  friend class AirlineTicketCalculatorFactory;
};

class SouthwestAirlineCalculator final : public AirlineCalculatorAbstract {

public:
  SouthwestAirlineCalculator() = default;

  [[nodiscard]] auto getOperationCost(double miles, TicketType ticketType) const
      -> double override {

    return costPerMile_usd_ * miles;
  }

  friend class AirlineTicketCalculatorFactory;

private:
  const double costPerMile_usd_{1.0};
};

class LuigiAirline final : public AirlineCalculatorAbstract {
public:
  LuigiAirline() = default;

  [[nodiscard]] auto getOperationCost(double miles, TicketType ticketType) const
      -> double override {

    double operationCost_usd{0.0};

    if (ticketType == TicketType::BUSINESS) {
      operationCost_usd = 50.0 + 0.25 * miles;
    } else if (ticketType == TicketType::PREMIUM) {
      operationCost_usd = 25.0;
    } else {
      operationCost_usd = 0.0;
    }

    return std::max(operationCost_usd, fixCost_usd_);
  }

private:
  const double fixCost_usd_{100.0};
};

// This solution has the flavor of the Abstract Factory pattern
// But it has a factory method that creates the concrete product instead of a
// factory class
static auto createAirlineTicket(std::string_view name)
    -> std::unique_ptr<AirlineCalculatorAbstract> {

  if (name == "United") {
    return std::make_unique<UnitedAirlineCalculator>();
  } else if (name == "Delta") {
    return std::make_unique<DeltaAirlineCalculator>();
  } else if (name == "Southwest") {
    return std::make_unique<SouthwestAirlineCalculator>();
  } else if (name == "LuigiAir") {
    return std::make_unique<LuigiAirline>();
  } else {
    throw std::invalid_argument("Unsupported airline.");
  }
}

int main() {
  const std::vector<std::string> airlines{
      "United 150.0 Premium", "Delta 60.0 Business", "Southwest 1000.0 Economy",
      "LuigiAir 50.0 Business"};

  for (const auto &airline : airlines) {
    std::istringstream iss(airline);
    std::string name;
    double miles;
    std::string ticket;
    iss >> name >> miles >> ticket;

    TicketType ticketType;
    if (ticket == "Economy") {
      ticketType = TicketType::ECONOMY;
    } else if (ticket == "Business") {
      ticketType = TicketType::BUSINESS;
    } else if (ticket == "Premium") {
      ticketType = TicketType::PREMIUM;
    } else {
      throw std::invalid_argument("Unsupported ticket type.");
    }

    const auto airlineCalculatorPtr = createAirlineTicket(name);

    std::cout << airlineCalculatorPtr->getOperationCost(miles, ticketType)
              << '\n';
  }

  return 0;
}