#include <iostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Achieve uniform initialization using initializer list

namespace html {
struct Tag
{
    std::string_view                                           name_;
    std::string_view                                           text_;
    std::vector<Tag>                                           children_;
    std::vector<std::pair<std::string_view, std::string_view>> attributes_;

    friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
    {
        os << "<" << tag.name_;

        for (const auto& att : tag.attributes_)
            os << " " << att.first << "=\"" << att.second << "\"";

        if (tag.children_.empty() && tag.text_.length() == 0) {
            os << "/>" << std::endl;
        } else {
            os << ">" << std::endl;

            if (tag.text_.length())
                os << tag.text_ << std::endl;

            for (const auto& child : tag.children_) {
                os << child;
            }

            os << "</" << tag.name_ << ">" << std::endl;
        }

        return os;
    }

protected:
    Tag(std::string_view name, std::string_view text)
        : name_{name}
        , text_{text}
    {}

    Tag(std::string_view name, std::vector<Tag> children)
        : name_{name}
        , children_{std::move(children)}
    {}
};

struct P : Tag
{
    explicit P(const std::string_view& text)
        : Tag{"p", text}
    {}

    P(std::initializer_list<Tag> children)
        : Tag("p", children)
    {}
};

struct IMG : Tag
{
    explicit IMG(const std::string_view& url)
        : Tag{"img", ""}
    {
        attributes_.emplace_back(make_pair("src", url));
    }
};
} // namespace html

int main()
{
    std::cout <<

      html::P{html::IMG{"http://pokemon.com/pikachu.png"}, html::IMG{"https://www.google.com/"}}

              << '\n';

    return 0;
}