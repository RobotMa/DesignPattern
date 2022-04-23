#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// no paranthesis
struct Token
{
    enum class Type
    {
        kDigit = 0,
        kVar,
        kPlus,
        kMinus
    } type_;
    std::string text_{};

    Token(Type type, std::string text)
        : type_{type}
        , text_{std::move(text)}
    {}

    friend std::ostream& operator<<(std::ostream& os, const Token& token)
    {
        os << token.text_;
        return os;
    }
};

std::vector<Token> lex(const std::string& expression)
{
    std::vector<Token> tokens;
    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        if (std::isdigit(c)) {
            std::ostringstream oss;
            oss << c;
            for (size_t j = i + 1; j < expression.size(); ++j) {
                if (std::isdigit(expression[j])) {
                    ++i;
                    oss << expression[j];
                } else {
                    break;
                }
            }
            tokens.emplace_back(Token::Type::kDigit, oss.str());
        } else {
            switch (c) {
                case '+':
                    tokens.emplace_back(Token::Type::kPlus, "+");
                    break;
                case '-':
                    tokens.emplace_back(Token::Type::kMinus, "-");
                    break;
                case 'a' ... 'z':
                    auto               isAlphabet = [](const char cha) { return 'A' <= cha && cha <= 'z'; };
                    std::ostringstream oss;
                    oss << c;
                    for (size_t j = i + 1; j < expression.size(); ++j) {
                        auto tmp = expression[j];
                        if (isAlphabet(tmp)) {
                            ++i;
                            oss << tmp;
                        } else {
                            break;
                        }
                    }
                    tokens.emplace_back(Token::Type::kVar, oss.str());
                    break;
            }
        }
    }
    return tokens;
}

struct Expression
{
    virtual ~Expression()  = default;
    virtual int evaluate() = 0;
};

struct Digit : Expression
{
    int num_;
    explicit Digit(int num)
        : num_(num)
    {}

    int evaluate() override { return num_; }
};

struct Variable : Expression
{
    int num_;
    explicit Variable(int num)
        : num_(num)
    {}
    int evaluate() override { return num_; }
};

struct BinaryOperaion : Expression
{
    enum class Type
    {
        kAdd = 0,
        kSubstract
    } type_;
    Expression* left;
    Expression* right;

    ~BinaryOperaion() override
    {
        delete left;
        delete right;
    }

    int evaluate() override
    {
        if (type_ == Type::kAdd) {
            return left->evaluate() + right->evaluate();
        }

        return left->evaluate() - right->evaluate();
    }
};

struct ExpressionProcessor
{
    std::unordered_map<char, int> variables;

    int calculate(const std::string& expression) const
    {
        auto lexed = lex(expression);

        auto bElement = new BinaryOperaion();
        bool hasLhs   = false;

        for (size_t i = 0; i < lexed.size(); ++i) {

            const auto token = lexed[i];
            auto       type  = token.type_;
            switch (type) {
                case Token::Type::kDigit: {
                    auto digit = new Digit{stoi(token.text_)};
                    if (!hasLhs) {
                        bElement->left = digit;
                        hasLhs         = true;
                    } else {
                        bElement->right = digit;
                    }
                    break;
                }
                case Token::Type::kVar: {
                    if (token.text_.size() != 1) {
                        return 0;
                    }

                    if (variables.find(token.text_[0]) == variables.end()) {
                        return 0;
                    }
                    auto var = new Variable{stoi(token.text_)};
                    if (!hasLhs) {
                        bElement->left = var;
                        hasLhs         = true;
                    } else {
                        bElement->right = var;
                    }
                    break;
                }
                case Token::Type::kPlus:
                    bElement->type_ = BinaryOperaion::Type::kAdd;
                    if (hasLhs) {
                    }
                    break;
                case Token::Type::kMinus:
                    bElement->type_ = BinaryOperaion::Type::kSubstract;
                    break;
            }
        }

        return bElement->evaluate();
    }
};

int main()
{
    const std::string expression1{"1+2+344"};
    const std::string expression2{"1+2+xy"};
    const std::string expression3{"10-2-x"};

    // check lexing function
    const auto lexed1 = lex(expression1);
    const auto lexed2 = lex(expression2);
    const auto lexed3 = lex(expression3);

    std::copy(lexed1.begin(), lexed1.end(), std::ostream_iterator<Token>(std::cout, " "));
    std::cout << '\n';
    std::copy(lexed2.begin(), lexed2.end(), std::ostream_iterator<Token>(std::cout, " "));
    std::cout << '\n';
    std::copy(lexed3.begin(), lexed3.end(), std::ostream_iterator<Token>(std::cout, " "));
    std::cout << '\n';

    const ExpressionProcessor ep1{std::unordered_map<char, int>{std::make_pair<char, int>('x', 2)}};
    std::cout << ep1.calculate(expression1) << '\n';
    std::cout << ep1.calculate(expression2) << '\n';
    std::cout << ep1.calculate(expression3) << '\n';

    return 0;
}