#include <algorithm>
#include <iostream>
#include <vector>

class BankAccount {
public:
  void deposit(int amount) {
    balance_ += amount;
    std::cout << "deposited " << amount << ", getBalance now " << balance_
              << "\n";
  }

  bool withdraw(int amount) {
    if (balance_ - amount >= overdraft_limit) {
      balance_ -= amount;
      std::cout << "withdrew " << amount << ", getBalance now " << balance_
                << "\n";
      return true;
    }

    return false;
  }

  int getBalance() const { return balance_; }

private:
  int balance_ = 0;
  int overdraft_limit = -500;
};

class Command {
public:
  virtual ~Command() = default;
  virtual void call() = 0;
  virtual void undo() = 0;
};

// should really be BankAccountCommand
class BankAccountCommand : public Command {
public:
  enum Action { deposit, withdraw } action_;

  BankAccountCommand(BankAccount &account, const Action action,
                     const int amount)
      : account_(account), action_(action), amount_(amount), succeeded_(false) {
  }

  void call() override {
    switch (action_) {
    case deposit:
      account_.deposit(amount_);
      succeeded_ = true;
      break;
    case withdraw:
      succeeded_ = account_.withdraw(amount_);
      break;
    }
  }

  void undo() override {
    if (!succeeded_) {
      return;
    }

    switch (action_) {
    case withdraw:
      account_.deposit(amount_);
      break;
    case deposit:
      account_.withdraw(amount_);
      break;
    }
  }

  // Note : non-virtual function
  [[nodiscard]] bool isSuccessful() const { return succeeded_; }

  // Note : non-virtual function
  void failToProcess() { succeeded_ = false; }

private:
  BankAccount &account_;
  bool succeeded_;
  int amount_;
};

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand : std::vector<BankAccountCommand>, Command {
  CompositeBankAccountCommand(const std::initializer_list<value_type> &items)
      : vector<BankAccountCommand>(items) {}

  void call() override {
    for (auto &cmd : *this) {
      cmd.call();
    }
  }

  void undo() override {
    for (auto it = rbegin(); it != rend(); ++it) {
      it->undo();
    }
  }
};

struct DependentCompositeCommand : CompositeBankAccountCommand {
  DependentCompositeCommand(const std::initializer_list<value_type> &inList)
      : CompositeBankAccountCommand{inList} {}

  void call() override {
    bool ok = true;
    for (auto &cmd : *this) {
      if (ok) {
        cmd.call();
        ok = cmd.isSuccessful();
      } else {
        // if one command fails, the subsequent commands should not be executed
        cmd.failToProcess();
      }
    }
  }
};

struct MoneyTransferCommand : DependentCompositeCommand {
  MoneyTransferCommand(BankAccount &from, BankAccount &to, int amount)
      : DependentCompositeCommand{
            BankAccountCommand{from, BankAccountCommand::withdraw, amount},
            BankAccountCommand{to, BankAccountCommand::deposit, amount}} {}
};

int main() {
  BankAccount ba1, ba2;

  /*vector<BankAccountCommand> commands{*/
  CompositeBankAccountCommand commands{
      BankAccountCommand{ba1, BankAccountCommand::deposit, 100},
      BankAccountCommand{ba2, BankAccountCommand::withdraw, 200}};

  std::cout << ba1.getBalance() << '\n';
  std::cout << ba2.getBalance() << '\n';

  commands.call();

  std::cout << ba1.getBalance() << '\n';
  std::cout << ba2.getBalance() << '\n';

  commands.undo();

  std::cout << ba1.getBalance() << '\n';
  std::cout << ba2.getBalance() << '\n';

  return 0;
}
