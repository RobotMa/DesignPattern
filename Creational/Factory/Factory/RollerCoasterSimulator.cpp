#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

enum class LiftType : uint8_t { Chain, Cable };

class AbstractRollerCoaster {
public:
  virtual double computeComfortScore() const = 0;
  virtual double computeOverallScore() const = 0;
};

class RollerCoasterImpl : public AbstractRollerCoaster {
public:
  RollerCoasterImpl(int maxSpeed, double bumpsPerSecond, LiftType liftType)
      : bumpsPerSecond_(bumpsPerSecond), maxSpeed_(maxSpeed),
        liftType_(liftType) {
    // check against invalid values
    // non positive speed or bumps per second
  }

  ~RollerCoasterImpl() = default;

  virtual double computeComfortScore() const override {
    double comfortScore{1.0};
    comfortScore = std::min(comfortScore, 1.0 / bumpsPerSecond_);
    comfortScore = std::min(comfortScore, 1.0 / static_cast<double>(maxSpeed_));
    return comfortScore;
  }

  double computeOverallScore() const override {

    const double comfortScore = computeComfortScore();
    return scaleFactor_ * comfortScore * static_cast<double>(maxSpeed_);
  }

protected:
  double scaleFactor_; // delegate to child class
  double bumpsPerSecond_;
  int maxSpeed_;
  LiftType liftType_;
};

class WoodenRollerCoaster : public RollerCoasterImpl {

public:
  WoodenRollerCoaster(int maxSpeed, double bumpsPerSecond, LiftType liftType)
      : RollerCoasterImpl(maxSpeed, bumpsPerSecond, liftType) {
    scaleFactor_ = 1.0;
  }
};

class SteelCoaster : public RollerCoasterImpl {

public:
  SteelCoaster(int maxSpeed, double bumpsPerSecond, LiftType liftType)
      : RollerCoasterImpl(maxSpeed, bumpsPerSecond, liftType) {
    scaleFactor_ = 2.0;
  }

  double computeComfortScore() const override {
    double comfortScore{1.0};
    comfortScore = std::min(comfortScore, 1.0 / bumpsPerSecond_);
    comfortScore = std::min(comfortScore, 5.0 / static_cast<double>(maxSpeed_));
    return comfortScore;
  }
};

class SuspendedCoaster : public RollerCoasterImpl {

public:
  SuspendedCoaster(int maxSpeed, double bumpsPerSecond, LiftType liftType)
      : RollerCoasterImpl(maxSpeed, bumpsPerSecond, liftType) {
    scaleFactor_ = 0.5;
  }

  double computeComfortScore() const override {

    const double comfortScore = RollerCoasterImpl::computeComfortScore();
    if (liftType_ == LiftType::Cable) {
      return comfortScore + 0.5;
    }

    return comfortScore;
  }
};

std::unique_ptr<RollerCoasterImpl> makeCoaster(std::string_view coasterType,
                                               int maxSpeed,
                                               double bumpsPerSecond,
                                               std::string_view liftTypeStr) {

  std::unordered_map<std::string_view, LiftType> liftTypeMap{
      {"Cable", LiftType::Cable}, {"Chain", LiftType::Chain}};

  if (coasterType == "Wooden") {
    return std::make_unique<WoodenRollerCoaster>(maxSpeed, bumpsPerSecond,
                                                 liftTypeMap[liftTypeStr]);
  } else if (coasterType == "Steel") {
    return std::make_unique<SteelCoaster>(maxSpeed, bumpsPerSecond,
                                          liftTypeMap[liftTypeStr]);

  } else if (coasterType == "Suspended") {
    return std::make_unique<SuspendedCoaster>(maxSpeed, bumpsPerSecond,
                                              liftTypeMap[liftTypeStr]);
  } else {
    throw std::invalid_argument("Invalid coaster type");
  }
}

int main() {
  std::tuple<std::string, int, double, std::string> coaster1{"Wooden", 4, 1.0,
                                                             "Chain"};
  std::tuple<std::string, int, double, std::string> coaster2{"Steel", 20, 2.0,
                                                             "Cable"};
  std::tuple<std::string, int, double, std::string> coaster3{"Suspended", 2,
                                                             1.5, "Cable"};
  std::tuple<std::string, int, double, std::string> coaster4{"Suspended", 2,
                                                             1.5, "Chain"};

  auto coaster1Ptr = makeCoaster(std::get<0>(coaster1), std::get<1>(coaster1),
                                 std::get<2>(coaster1), std::get<3>(coaster1));
  auto coaster2Ptr = makeCoaster(std::get<0>(coaster2), std::get<1>(coaster2),
                                 std::get<2>(coaster2), std::get<3>(coaster2));
  auto coaster3Ptr = makeCoaster(std::get<0>(coaster3), std::get<1>(coaster3),
                                 std::get<2>(coaster3), std::get<3>(coaster3));
  auto coaster4Ptr = makeCoaster(std::get<0>(coaster4), std::get<1>(coaster4),
                                 std::get<2>(coaster4), std::get<3>(coaster4));

  std::cout << coaster1Ptr->computeOverallScore() << '\n';
  std::cout << coaster2Ptr->computeOverallScore() << '\n';
  std::cout << coaster3Ptr->computeOverallScore() << '\n';
  std::cout << coaster4Ptr->computeOverallScore() << '\n';

  const std::vector<double> results{1.0, 10.0, 1.0, 0.5};
  return 0;
}