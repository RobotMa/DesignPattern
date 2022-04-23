#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct BankAccount
{
    int balance_        = 0;
    int overdraft_limit = -500;

    void deposit(int amount)
    {
        balance_ += amount;
        cout << "deposited " << amount << ", balance_ now " << balance_ << "\n";
    }

    bool withdraw(int amount)
    {
        if (balance_ - amount >= overdraft_limit) {
            balance_ -= amount;
            cout << "withdrew " << amount << ", balance_ now " << balance_ << "\n";
            return true;
        }
        return false;
    }
};

struct Command
{
    bool succeeded;
    virtual ~Command()  = default;
    virtual void call() = 0;
    virtual void undo() = 0;
};

// should really be BankAccountCommand
struct BankAccountCommand : Command
{
    BankAccount& account_;
    enum Action
    {
        deposit,
        withdraw
    } action_;
    int amount_;

    BankAccountCommand(BankAccount& account, const Action action, const int amount)
        : account_(account)
        , action_(action)
        , amount_(amount)
    {
        succeeded = false;
    }

    void call() override
    {
        switch (action_) {
            case deposit:
                account_.deposit(amount_);
                succeeded = true;
                break;
            case withdraw:
                succeeded = account_.withdraw(amount_);
                break;
        }
    }

    void undo() override
    {
        if (!succeeded)
            return;

        switch (action_) {
            case withdraw:
                if (succeeded)
                    account_.deposit(amount_);
                break;
            case deposit:
                account_.withdraw(amount_);
                break;
        }
    }
};

// vector doesn't have virtual dtor, but who cares?
struct CompositeBankAccountCommand
    : vector<BankAccountCommand>
    , Command
{
    CompositeBankAccountCommand(const initializer_list<value_type>& items)
        : vector<BankAccountCommand>(items)
    {}

    void call() override
    {
        for (auto& cmd : *this)
            cmd.call();
    }

    void undo() override
    {
        for (auto it = rbegin(); it != rend(); ++it)
            it->undo();
    }
};

struct DependentCompositeCommand : CompositeBankAccountCommand
{
    explicit DependentCompositeCommand(const initializer_list<value_type>& Ilist)
        : CompositeBankAccountCommand{Ilist}
    {}

    void call() override
    {
        bool ok = true;
        for (auto& cmd : *this) {
            if (ok) {
                cmd.call();
                ok = cmd.succeeded;
            } else {
                cmd.succeeded = false;
            }
        }
    }
};

struct MoneyTransferCommand : DependentCompositeCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
        : DependentCompositeCommand{BankAccountCommand{from, BankAccountCommand::withdraw, amount},
                                    BankAccountCommand{to, BankAccountCommand::deposit, amount}}
    {}
};

int main()
{
    BankAccount ba1, ba2;
    /*vector<BankAccountCommand> commands{*/
    CompositeBankAccountCommand commands{BankAccountCommand{ba1, BankAccountCommand::deposit, 100},
                                         BankAccountCommand{ba2, BankAccountCommand::withdraw, 200}};

    cout << ba1.balance_ << endl;
    cout << ba2.balance_ << endl;

    commands.call();

    cout << ba1.balance_ << endl;
    cout << ba2.balance_ << endl;

    commands.undo();

    cout << ba1.balance_ << endl;
    cout << ba2.balance_ << endl;

    getchar();
    return 0;
}
