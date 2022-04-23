#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class FormattedText
{
private:
    std::string_view  plainText_;
    std::vector<bool> caps;

public:
    explicit FormattedText(std::string_view plainText)
        : plainText_{plainText}
    {
        caps.reserve(plainText.length());
    }

    void capitalize(unsigned long start, unsigned long end)
    {
        for (unsigned long i = start; i <= end; ++i)
            caps[i] = true;
    }

    friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj)
    {
        std::string s;
        for (size_t i = 0; i < obj.plainText_.length(); ++i) {
            char c = obj.plainText_[i];
            s += (obj.caps[i] ? static_cast<char>(toupper(c)) : c);
        }
        return os << s;
    }
};

class BetterFormattedText
{
public:
    struct TextRange
    {
        size_t start, end;
        bool   capitalize;

        [[nodiscard]] bool covers(size_t position) const { return position >= start && position <= end; }
    };

    TextRange& get_range(size_t start, size_t end)
    {
        formatting_.emplace_back(TextRange{start, end, false});
        return *formatting_.rbegin();
    }

    explicit BetterFormattedText(std::string_view plainText)
        : plainText_{plainText}
    {}

    friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& obj)
    {
        std::string s;
        for (size_t i = 0; i < obj.plainText_.length(); i++) {
            auto c = obj.plainText_[i];
            for (const auto& rng : obj.formatting_) {
                if (rng.covers(i) && rng.capitalize)
                    c = static_cast<char>(toupper(c));
                s += c;
            }
        }
        return os << s;
    }

private:
    std::string_view       plainText_;
    std::vector<TextRange> formatting_;
};

int main()
{
    FormattedText ft("This is a brave new world");
    ft.capitalize(10, 15);
    std::cout << ft << '\n';

    BetterFormattedText bft("This is a brave new world");
    bft.get_range(10, 15).capitalize = true;
    std::cout << bft << '\n';

    return 0;
}
