// visitor examples for design patterns c++ book
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Expression
{
    virtual ~Expression()                  = default;
    virtual void print(ostringstream& oss) = 0;
};

struct DoubleExpression : Expression
{
    double value_;
    explicit DoubleExpression(const double value)
        : value_{value}
    {}

    void print(ostringstream& oss) override { oss << value_; }
};

struct AdditionExpression : Expression
{
    Expression *left_, *right_;

    AdditionExpression(Expression* const left, Expression* const right)
        : left_{left}
        , right_{right}
    {}

    ~AdditionExpression() override
    {
        delete left_;
        delete right_;
    }

    void print(ostringstream& oss) override
    {
        oss << "(";
        left_->print(oss);
        oss << "+";
        right_->print(oss);
        oss << ")";
    }
};

int main()
{
    auto          e = new AdditionExpression{new DoubleExpression{1},
                                    new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};
    ostringstream oss;
    e->print(oss);
    cout << oss.str() << endl;
}