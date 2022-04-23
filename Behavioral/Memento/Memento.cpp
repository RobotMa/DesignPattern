#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Memento
{
private:
    int balance_;

public:
    explicit Memento(int balance)
        : balance_(balance)
    {}
    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount
{
private:
    int balance_ = 0;

public:
    explicit BankAccount(const int balance)
        : balance_(balance)
    {}

    Memento deposit(int amount)
    {
        balance_ += amount;
        return Memento{balance_};
    }

    void restore(const Memento& m) { balance_ = m.balance_; }

    friend ostream& operator<<(ostream& os, const BankAccount& obj) { return os << "balance_: " << obj.balance_; }
};

class BankAccount2 // supports undo/redo
{
private:
    int                         balance_ = 0;
    vector<shared_ptr<Memento>> changes_;
    size_t                      current_;

public:
    explicit BankAccount2(const int balance)
        : balance_(balance)
    {
        changes_.emplace_back(make_shared<Memento>(balance));
        current_ = 0;
    }

    shared_ptr<Memento> deposit(int amount)
    {
        balance_ += amount;
        auto m = make_shared<Memento>(balance_);
        changes_.push_back(m);
        ++current_;
        return m;
    }

    void restore(const shared_ptr<Memento>& m)
    {
        if (m != nullptr) {
            balance_ = m->balance_;
            changes_.push_back(m);
            current_ = changes_.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if (current_ > 0) {
            --current_;
            auto m   = changes_[current_];
            balance_ = m->balance_;
            return m;
        }

        return nullptr;
    }

    shared_ptr<Memento> redo()
    {
        if (current_ + 1 < changes_.size()) {
            ++current_;
            auto m   = changes_[current_];
            balance_ = m->balance_;
            return m;
        }

        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const BankAccount2& obj) { return os << "balance_: " << obj.balance_; }
};

void memento()
{
    BankAccount ba{100};
    const auto  m1 = ba.deposit(50); // 150
    const auto  m2 = ba.deposit(25); // 175
    cout << ba << "\n";

    // undo to m1
    ba.restore(m1);
    cout << ba << "\n";

    // redo
    ba.restore(m2);
    cout << ba << "\n";
}

void undo_redo()
{
    BankAccount2 ba{100};
    ba.deposit(50);
    ba.deposit(25); // 125
    cout << ba << "\n";

    ba.undo();
    cout << "Undo 1: " << ba << "\n";
    ba.undo();
    cout << "Undo 2: " << ba << "\n";
    ba.redo();
    cout << "Redo 2: " << ba << "\n";

    ba.undo();
}

int main()
{
    memento();
    undo_redo();

    return 0;
}
