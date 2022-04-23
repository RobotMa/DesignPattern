// visitor examples for design patterns c++ book
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct Expression
{
    virtual ~Expression() = default;
};

struct DoubleExpression : Expression
{
    double value_;
    explicit DoubleExpression(const double value)
        : value_{value}
    {}
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
};

struct ExpressionPrinter
{
    /*void print(DoubleExpression *de, ostringstream& oss) const
    {
      oss << de->value;
    }
    void print(AdditionExpression *ae, ostringstream& oss) const
    {
      oss << "(";
      print(ae->left, oss);
      oss << "+";
      print(ae->right, oss);
      oss << ")";
    }*/
    ostringstream oss_;

    void print(Expression* e)
    {
        if (auto de = dynamic_cast<DoubleExpression*>(e)) {
            oss_ << de->value_;
        } else if (auto ae = dynamic_cast<AdditionExpression*>(e)) {
            oss_ << "(";
            print(ae->left_);
            oss_ << "+";
            print(ae->right_);
            oss_ << ")";
        }
    }

    string str() const { return oss_.str(); }
};

int main()
{
    auto          e = new AdditionExpression{new DoubleExpression{1},
                                    new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};
    ostringstream oss;
    // e->print(oss);
    ExpressionPrinter ep;
    ep.print(e);
    cout << ep.str() << endl;
}