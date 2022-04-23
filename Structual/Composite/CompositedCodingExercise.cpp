#include <numeric>
#include <vector>

#include <gtest/gtest.h>

using namespace std;

struct ContainsIntegers
{
    virtual int sum()           = 0;
    virtual ~ContainsIntegers() = default;
};

struct SingleValue : ContainsIntegers
{
    int value_{0};

    SingleValue() = default;

    explicit SingleValue(const int value)
        : value_{value}
    {}

    int sum() override { return value_; }
};

struct ManyValues
    : vector<int>
    , ContainsIntegers
{
    void add(const int value) { push_back(value); }

    int sum() override { return accumulate(begin(), end(), 0); }
};

int sum(const vector<ContainsIntegers*>& items)
{
    int result{0};
    for (auto item : items)
        result += item->sum();
    return result;
}

namespace {
class Evaluate : public testing::Test
{};

TEST_F(Evaluate, SimpleTest)
{
    SingleValue single_value{11};
    ManyValues  other_values;
    other_values.add(22);
    other_values.add(33);
    ASSERT_EQ(66, sum({&single_value, &other_values}));
}

} // namespace

int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}