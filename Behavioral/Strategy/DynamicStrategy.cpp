#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class OutputFormat
{
    Markdown,
    Html
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    // Clever Integration Segregation Principle : clients shouldn't be forced to depend on interfaces that they do not
    // use
    // Have definitions for all virtual functions so that the child classes don't have to explicitly define everyone
    // of them
    virtual void addListItem(ostringstream& oss, const string& item)
    {
        (void)oss;
        (void)item;
    };
    virtual void start(ostringstream& oss) { (void)oss; };
    virtual void end(ostringstream& oss) { (void)oss; };
};

struct MarkdownListStrategy : ListStrategy
{
    void addListItem(ostringstream& oss, const string& item) override { oss << " * " << item << endl; }
};

struct HtmlListStrategy : ListStrategy
{
    void addListItem(ostringstream& oss, const string& item) override { oss << "<li>" << item << "</li>" << endl; }

    void start(ostringstream& oss) override { oss << "<ul>" << endl; }

    void end(ostringstream& oss) override { oss << "</ul>" << endl; }
};

struct TextProcessor
{
    void clear()
    {
        oss_.str("");
        oss_.clear();
    }

    void appendList(const vector<string> items)
    {
        listStrategy_->start(oss_);
        for (auto& item : items) {
            listStrategy_->addListItem(oss_, item);
        }
        listStrategy_->end(oss_);
    }

    void set_output_format(const OutputFormat format)
    {
        switch (format) {
            case OutputFormat::Markdown:
                listStrategy_ = make_unique<MarkdownListStrategy>();
                break;
            case OutputFormat::Html:
                listStrategy_ = make_unique<HtmlListStrategy>();
                break;
            default:
                throw runtime_error("Unsupported strategy.");
        }
    }

    string str() const { return oss_.str(); }

private:
    ostringstream            oss_;
    unique_ptr<ListStrategy> listStrategy_;
};

int main()
{
    // markdown
    TextProcessor tp;
    tp.set_output_format(OutputFormat::Markdown);
    tp.appendList({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    // html
    tp.clear();
    tp.set_output_format(OutputFormat::Html);
    tp.appendList({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    getchar();
    return 0;
}
