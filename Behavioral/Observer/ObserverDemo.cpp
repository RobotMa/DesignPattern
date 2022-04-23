#include "Headers.hpp"
#include "Observer.hpp"
#include "SaferObservable.hpp"

class Person : public SaferObservable<Person>
{
private:
    int         age_;
    std::string name_;

public:
    explicit Person(int age, std::string name)
        : age_(age)
        , name_{std::move(name)}
    {}

    virtual ~Person() = default;

    [[nodiscard]] int         getAge() const { return age_; }
    [[nodiscard]] std::string getName() const { return name_; }

    void setAge(int age)
    {
        if (age_ == age) {
            return;
        }

        age_ = age;
        notify(*this, "age");

        const bool prevCanVote = getCanVote();
        if (prevCanVote != getCanVote()) {
            notify(*this, "can vote");
        }
    }

    [[nodiscard]] bool getCanVote() const { return age_ >= 16; }
};

// observer & observable

class ConsolePersonObserver : public Observer<Person>
{
public:
    void fieldChanged(Person& source, const std::string& field_name) override
    {
        std::cout << "Person's " << field_name << " has changed to ";
        if (field_name == "age") {
            std::cout << source.getAge();
        }
        if (field_name == "can vote") {
            std::cout << std::boolalpha << source.getCanVote();
        }
        std::cout << ".\n";
    }
};

class TrafficAdministration : public Observer<Person>
{
public:
    void fieldChanged(Person& source, const std::string& fieldName) override
    {
        if (fieldName == "age") {
            if (source.getAge() < 17) {
                std::cout << "Whoa there, you're not old enough to drive!\n";
            } else {
                std::cout << "Oh, ok, we no longer care!\n";
                source.unsubscribe(*this);
            }
        }
    }
};

void runObserverPattern()
{
    std::cout << "Home brewed observer pattern \n";
    TrafficAdministration ta;
    ConsolePersonObserver cp;

    Person p1{14, "John"};
    p1.subscribe(ta);

    p1.setAge(15);
    p1.setAge(16);
    try {
        p1.setAge(17);
    } catch (const std::exception& e) {
        std::cout << "Oops, " << e.what() << "\n";
    }

    Person p2{15, "Jimmy"};
    p2.subscribe(ta);
    p2.subscribe(cp);

    p2.setAge(14);
}

// Boost based observer pattern
// Note: boost signal is not thread safe, so for multi threaded purpose, you will have to use the homebrewed version
template<typename T>
class BoostObservable
{
public:
    boost::signals2::signal<void(const std::string&)> fieldChanged;
};

class Person2 : public BoostObservable<Person2>
{
private:
    int age_;

public:
    explicit Person2(int age)
        : age_{age}
    {}
    void setAge(int age)
    {
        if (age_ == age)
            return;
        age_ = age;
        fieldChanged("age");
    }
};

void runBoostObserverPattern()
{
    std::cout << "\nBoost based observer pattern \n";
    Person2 p{15};
    auto    conn =
      p.fieldChanged.connect([](const std::string& fieldName) { std::cout << fieldName << " has changed \n"; });

    p.setAge(15);
    p.setAge(16);

    conn.disconnect();
    p.setAge(17);
}

int main()
{
    runObserverPattern();
    runBoostObserverPattern();

    return 0;
}