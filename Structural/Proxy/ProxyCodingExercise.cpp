#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
using namespace std;

class Person
{
private:
    int age_;

public:
    explicit Person(int age)
        : age_(age)
    {}

    [[nodiscard]] int getAge() const { return age_; }
    void              setAge(int age) { this->age_ = age; }

    [[nodiscard]] string_view drink() const noexcept { return "drinking"; }
    [[nodiscard]] string_view drive() const noexcept { return "driving"; }
    [[nodiscard]] string_view drink_and_drive() const noexcept { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
    explicit ResponsiblePerson(const Person& person)
        : person_(person)
    {}

    [[nodiscard]] int get_age() const { return person_.getAge(); }
    void              set_age(int value) { person_.setAge(value); }

    [[nodiscard]] string_view drink() const
    {
        if (get_age() >= 18)
            return person_.drink();

        return "too young";
    }

    [[nodiscard]] string_view drive() const
    {
        if (get_age() >= 16)
            return person_.drive();

        return "too young";
    }

    [[nodiscard]] string_view drink_and_drive() const { return "dead"; }

private:
    Person person_;
};

namespace {
class Evaluate : public testing::Test
{
public:
};

TEST_F(Evaluate, BaselineTest)
{
    Person            p{10};
    ResponsiblePerson rp{p};

    ASSERT_EQ("too young", rp.drive());
    ASSERT_EQ("too young", rp.drink());
    ASSERT_EQ("dead", rp.drink_and_drive());

    rp.set_age(20);

    ASSERT_EQ("driving", rp.drive());
    ASSERT_EQ("drinking", rp.drink());
    ASSERT_EQ("dead", rp.drink_and_drive());
}

} // namespace

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}