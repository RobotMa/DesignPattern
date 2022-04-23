#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class HtmlBuilder;

class HtmlElement
{
private:
    string_view              name_;
    string_view              text_;
    std::vector<HtmlElement> elements_;
    static constexpr size_t  indent_size_ = 2;

public:
    HtmlElement() = default;
    HtmlElement(string_view name, string_view text)
        : name_(name)
        , text_(text)
    {}

    [[nodiscard]] string str(int indent = 0) const
    {
        ostringstream oss;
        string        i(indent_size_ * static_cast<unsigned short>(indent), ' ');
        oss << i << "<" << name_ << ">" << endl;
        if (!text_.empty())
            oss << string(indent_size_ * (static_cast<unsigned short>(indent + 1)), ' ') << text_ << endl;

        for (const auto& e : elements_)
            oss << e.str(indent + 1);

        oss << i << "</" << name_ << ">" << endl;
        return oss.str();
    }

    // Option 1: friend builder class
    friend HtmlBuilder;

    // Option 2: static build functilon
    static unique_ptr<HtmlBuilder> build(const string& root_name) { return make_unique<HtmlBuilder>(root_name); }
};

class HtmlBuilder
{
public:
    explicit HtmlBuilder(const string_view& root_name) { root_.name_ = root_name; }

    // void to start with
    HtmlBuilder& add_child(const string_view& child_name, const string_view& child_text)
    {
        root_.elements_.emplace_back(child_name, child_text);
        return *this;
    }

    // pointer based
    HtmlBuilder* add_child_2(const string_view& child_name, const string_view& child_text)
    {
        root_.elements_.emplace_back(child_name, child_text);
        return this;
    }

    [[nodiscard]] string str() const noexcept { return root_.str(); }

    explicit operator HtmlElement() const { return root_; }

private:
    HtmlElement root_;
};

int main()
{
    // <p>hello</p>
    std::cout << "Non-builder output 1 : \n";
    auto   text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    printf("<p>%s</p> \n\n", text);

    // <ul><li>hello</li><li>world</li></ul>
    std::cout << "Non-builder output 2 : \n";
    string        words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul> \n";
    for (auto w : words)
        oss << "  <li>" << w << "</li> \n";
    oss << "</ul>";
    printf("%s \n\n", oss.str().c_str());

    // easier
    std::cout << "Builder output : \n";
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << '\n';

    auto builtElement = HtmlElement::build("ul")->add_child_2("li", "hello")->add_child_2("li", "world");
    cout << builtElement << '\n';
    cout << builder.operator HtmlElement().str() << '\n';

    return 0;
}