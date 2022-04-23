#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// cyclic visitor: based on function overloading
//                 works only on a stable hierarchy
// acyclic visitor: based on RTTI
//                  no hierarchy limitations, but slower

template<typename Visitable>
struct Visitor
{
    virtual ~Visitor()                 = default;
    virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase // marker interface
{
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(VisitorBase& obj)
    {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV*>(&obj))
            ev->visit(*this);
    }
};

struct DoubleExpression : Expression
{
    double value_;

    explicit DoubleExpression(double value)
        : value_(value)
    {}

    void accept(VisitorBase& obj) override
    {
        using DEV = Visitor<DoubleExpression>;
        if (auto ev = dynamic_cast<DEV*>(&obj))
            ev->visit(*this);
    }
};

struct AdditionExpression : Expression
{
    Expression *left_, *right_;

    AdditionExpression(Expression* left, Expression* right)
        : left_(left)
        , right_(right)
    {}

    ~AdditionExpression() override
    {
        delete left_;
        delete right_;
    }

    void accept(VisitorBase& obj) override
    {
        using AEV = Visitor<AdditionExpression>;
        if (auto ev = dynamic_cast<AEV*>(&obj))
            ev->visit(*this);
    }
};

struct ExpressionPrinter
    : VisitorBase
    , Visitor<Expression>
    , Visitor<DoubleExpression> // Can comment out along with visit(DoubleExpression) without failure
    , Visitor<AdditionExpression>
{
    void visit(Expression& obj) override
    {
        // fallback?
        (void)obj;
    }

    // can remove double visitor without failure
    void visit(DoubleExpression& obj) override { oss_ << obj.value_; }

    void visit(AdditionExpression& obj) override
    {
        oss_ << "(";
        obj.left_->accept(*this);
        oss_ << "+";
        obj.right_->accept(*this);
        oss_ << ")";
    }

    string str() const { return oss_.str(); }

private:
    ostringstream oss_;
};

int main()
{
    auto e = new AdditionExpression{new DoubleExpression{1},
                                    new AdditionExpression{new DoubleExpression{2}, new DoubleExpression{3}}};

    ExpressionPrinter ep;
    ep.visit(*e);
    cout << ep.str() << "\n";

    // getchar();
    return 0;
}
