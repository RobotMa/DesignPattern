#include <sstream>
#include <string>

#include <gtest/gtest.h>

using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor
{
    virtual ~ExpressionVisitor()                      = default;
    virtual void visit(Value& value)                 = 0;
    virtual void visit(AdditionExpression& ae)       = 0;
    virtual void visit(MultiplicationExpression& me) = 0;
};

struct Expression
{
    virtual ~Expression()                     = default;
    virtual void accept(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
    int value_;

    explicit Value(int value)
        : value_(value)
    {}

    void accept(ExpressionVisitor& ev) override { ev.visit(*this); }
};

struct AdditionExpression : Expression
{
    Expression &lhs_;
    Expression &rhs_;

    AdditionExpression(Expression& lhs, Expression& rhs)
        : lhs_(lhs)
        , rhs_(rhs)
    {}

    void accept(ExpressionVisitor& ev) override { ev.visit(*this); }
};

struct MultiplicationExpression : Expression
{
    Expression &lhs_;
    Expression &rhs_;

    MultiplicationExpression(Expression& lhs, Expression& rhs)
        : lhs_(lhs)
        , rhs_(rhs)
    {}

    void accept(ExpressionVisitor& ev) override { ev.visit(*this); }
};

struct ExpressionPrinter : ExpressionVisitor
{
    void visit(Value& value) override { oss_ << value.value_; }

    void visit(AdditionExpression& ae) override
    {
        oss_ << "(";
        ae.lhs_.accept(*this);
        oss_ << "+";
        ae.rhs_.accept(*this);
        oss_ << ")";
    }

    void visit(MultiplicationExpression& me) override
    {
        me.lhs_.accept(*this);
        oss_ << "*";
        me.rhs_.accept(*this);
    }

    string str() const { return oss_.str(); }

private:
    ostringstream oss_;
};

namespace {

class Evaluate : public ::testing::Test
{};

TEST_F(Evaluate, SimpleAddition)
{
    Value              v{2};
    AdditionExpression simple{v, v};
    ExpressionPrinter  ep;
    ep.visit(simple);
    ASSERT_EQ("(2+2)", ep.str());
}

TEST_F(Evaluate, ProductOfAdditionAndValue)
{
    Value                    _2{2};
    Value                    _3{3};
    Value                    _4{4};
    AdditionExpression       ae{_2, _3};
    MultiplicationExpression expr{ae, _4};
    ExpressionPrinter        ep;
    ep.visit(expr);
    ASSERT_EQ("(2+3)*4", ep.str());
}

} // namespace

int main(int ac, char* av[])
{
    //::testing::GTEST_FLAG(catch_exceptions) = false;
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}