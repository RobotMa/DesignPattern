#include <cstdint>
#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>

// boost.flyweight

// naive
using key = uint32_t;

// mmorpg
// Note : let's always use pass by value for std::string_view
// https://quuxplusone.github.io/blog/2021/11/09/pass-string-view-by-value/
struct User
{
    User(std::string_view first_name, std::string_view last_name)
        : firstName_{add(first_name)}
        , lastName_{add(last_name)}
    {}

    [[nodiscard]] std::string_view getFirstName() const { return names.left.find(firstName_)->second; }

    [[nodiscard]] std::string_view getLastName() const { return names.left.find(lastName_)->second; }

    static void info()
    {
        for (const auto& entry : names.left) {
            std::cout << "Key: " << entry.first << ", Value: " << entry.second << '\n';
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const User& obj)
    {
        return os << "firstName_: " << obj.firstName_ << " " << obj.getFirstName() << " last_name: " << obj.lastName_
                  << " " << obj.getLastName();
    }

protected:
    static key add(std::string_view s)
    {
        auto it = names.right.find(s);
        if (it == names.right.end()) {
            // add it
            key id = ++seed;
            names.insert(boost::bimap<key, std::string_view>::value_type(seed, s));
            return id;
        }
        return it->second;
    }

    // the data members below are the key to this naive implementation
    static boost::bimap<key, std::string_view> names;
    static key                                 seed;
    key                                        firstName_, lastName_;
};

key                                 User::seed = 0;
boost::bimap<key, std::string_view> User::names{};

void naive_flyweight()
{
    User john_doe{"John", "Doe"};
    User jane_doe{"Jane", "Doe"};

    std::cout << "John " << john_doe << '\n';
    std::cout << "Jane " << jane_doe << '\n';

    User::info();
}

struct User2
{
    // users share names! e.g., John Smith
    boost::flyweights::flyweight<std::string> firstName_, lastName_;
    // string firstName_, last_name;
    // ...
    User2(const std::string& firstName, const std::string& lastName)
        : firstName_(firstName)
        , lastName_(lastName)
    {}

    friend std::ostream& operator<<(std::ostream& os, const User2& user2)
    {
        os << "firstName_: " << user2.firstName_ << " lastName_: " << user2.lastName_;
        return os;
    }
};

void boost_flyweight()
{
    std::cout << "\nBoost Flyweight \n";
    User2 john_doe{"John", "Doe"};
    User2 jane_doe{"Jane", "Doe"};

    std::cout << john_doe << '\n';
    std::cout << jane_doe << '\n';

    std::cout << std::boolalpha << (&jane_doe.firstName_.get() == &john_doe.firstName_.get()) << '\n';
    std::cout << std::boolalpha << (&jane_doe.lastName_.get() == &john_doe.lastName_.get()) << '\n';
}

int main()
{
    naive_flyweight();
    boost_flyweight();

    return 0;
}
