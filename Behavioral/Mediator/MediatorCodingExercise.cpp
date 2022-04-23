#include <memory>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

class IParticipant : public std::enable_shared_from_this<IParticipant>
{
public:
    virtual void              notify(std::shared_ptr<IParticipant> sender, int value) = 0;
    [[nodiscard]] virtual int getValue() const                                        = 0;
    virtual ~IParticipant()                                                           = default;
};

class Mediator
{
public:
    void broadcast(const std::shared_ptr<IParticipant>& sender, int value) const
    {
        for (const auto& p : participants_) {
            p->notify(sender, value);
        }
    }

    void addParticipant(const std::shared_ptr<IParticipant>& p) { participants_.push_back(p); }

private:
    std::vector<std::shared_ptr<IParticipant>> participants_{};
};

class Participant : public IParticipant
{
public:
    void join(const std::shared_ptr<Mediator>& mediator)
    {
        mediator_ = mediator;
        mediator_->addParticipant(shared_from_this());
    }

    void notify(std::shared_ptr<IParticipant> sender, int value) override
    {
        if (sender != shared_from_this())
            this->value_ += value;
    }

    [[nodiscard]] int getValue() const override { return value_; }

    void say(int value) { mediator_->broadcast(shared_from_this(), value); }

private:
    int                       value_{0};
    std::shared_ptr<Mediator> mediator_{nullptr};
};

namespace {

class Evaluate : public ::testing::Test
{};

TEST_F(Evaluate, LongMediationTest)
{
    auto m  = std::make_shared<Mediator>();
    auto p1 = std::make_shared<Participant>();
    auto p2 = std::make_shared<Participant>();

    p1->join(m);
    p2->join(m);

    ASSERT_EQ(0, p1->getValue());
    ASSERT_EQ(0, p2->getValue());

    p1->say(2);

    ASSERT_EQ(0, p1->getValue());
    ASSERT_EQ(2, p2->getValue());

    p2->say(4);

    ASSERT_EQ(4, p1->getValue());
    ASSERT_EQ(2, p2->getValue());
}

} // namespace
