#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <boost/lexical_cast.hpp>

using namespace std;

struct Token
{
    enum Type
    {
        integer,
        plus,
        minus,
        lparen,
        rparen
    } type_;
    string text_;

    explicit Token(Type type, string text)
        : type_{type}
        , text_{std::move(text)}
    {}

    friend ostream& operator<<(ostream& os, const Token& obj) { return os << "`" << obj.text_ << "`"; }
};

struct Element
{
    virtual ~Element()       = default;
    virtual int eval() const = 0;
};

struct Integer : Element
{
    int value_;
    explicit Integer(const int value)
        : value_(value)
    {}
    [[nodiscard]] int eval() const override { return value_; }
};

struct BinaryOperation : Element
{
    enum Type
    {
        addition,
        subtraction
    } type;
    shared_ptr<Element> lhs, rhs;

    [[nodiscard]] int eval() const override
    {
        if (type == addition) {
            return lhs->eval() + rhs->eval();
        }

        return lhs->eval() - rhs->eval();
    }
};

shared_ptr<Element> parse(const vector<Token>& tokens)
{
    auto result   = make_unique<BinaryOperation>();
    bool have_lhs = false;
    for (size_t i = 0; i < tokens.size(); i++) {
        auto token = tokens[i];
        switch (token.type_) {
            case Token::integer: {
                int  value   = boost::lexical_cast<int>(token.text_);
                auto integer = make_shared<Integer>(value);
                if (!have_lhs) {
                    result->lhs = integer;
                    have_lhs    = true;
                } else {
                    result->rhs = integer;
                }
            } break;
            case Token::plus:
                result->type = BinaryOperation::addition;
                break;
            case Token::minus:
                result->type = BinaryOperation::subtraction;
                break;
            case Token::lparen: {
                size_t j = i;
                for (; j < tokens.size(); ++j) {
                    if (tokens[j].type_ == Token::rparen)
                        break; // found it!
                }

                vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
                for(const auto&e : subexpression)
                {
                    std::cout << e.text_ << " ";
                }
                std::cout << "\n\n";
                const auto    element = parse(subexpression);
                if (!have_lhs) {
                    result->lhs = element;
                    have_lhs    = true;
                } else {
                    result->rhs = element;
                }
                i = j; // advance
            } break;
            case Token::rparen:
                break;
        }
    }
    return result;
}

vector<Token> lex(const string& input)
{
    vector<Token> result;

    for (size_t i = 0; i < input.size(); ++i) {
        switch (input[i]) {
            case '+':
                result.emplace_back(Token::plus, "+");
                break;
            case '-':
                result.emplace_back(Token::minus, "-");
                break;
            case '(':
                result.emplace_back(Token::lparen, "(");
                break;
            case ')':
                result.emplace_back(Token::rparen, ")");
                break;
            default:
                // number
                ostringstream buffer;
                buffer << input[i];
                for (size_t j = i + 1; j < input.size(); ++j) {
                    if (isdigit(input[j])) {
                        buffer << input[j];
                        ++i;
                    } else {
                        result.emplace_back(Token::integer, buffer.str());
                        break;
                    }
                }
        }
    }

    return result;
}

int main()
{
    const string input{"(13-4)-(12+1)"}; // see if you can make nested braces work
    const auto   tokens = lex(input);

    // let's see the tokens_
    for (auto& t : tokens)
        cout << t << "   ";
    cout << endl;

    try {
        auto parsed = parse(tokens);
        cout << input << " = " << parsed->eval() << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    getchar();
    return 0;
}
