#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// Strategy is represented by a class hierarchy and specified by enum
enum class OutputFormat : uint8_t { Markdown, Html };

struct ListStrategy {
  virtual ~ListStrategy() = default;
  // Clever Integration Segregation Principle : clients shouldn't be forced to
  // depend on interfaces that they do not use Have definitions for all virtual
  // functions so that the child classes don't have to explicitly define
  // everyone of them
  virtual void addListItem(std::ostringstream &oss, const std::string &item) {
    (void)oss;
    (void)item;
  };
  virtual void start(std::ostringstream &oss) { (void)oss; };
  virtual void end(std::ostringstream &oss) { (void)oss; };
};

struct MarkdownListStrategy : ListStrategy {
  void addListItem(std::ostringstream &oss, const std::string &item) override {
    oss << " * " << item << '\n';
  }
};

struct HtmlListStrategy : ListStrategy {
  void addListItem(std::ostringstream &oss, const std::string &item) override {
    oss << "<li>" << item << "</li>" << '\n';
  }

  void start(std::ostringstream &oss) override { oss << "<ul>" << '\n'; }

  void end(std::ostringstream &oss) override { oss << "</ul>" << '\n'; }
};

class TextProcessor {
public:
  void clear() {
    oss_.str("");
    oss_.clear();
  }

  void appendList(const std::vector<std::string> &items) {
    listStrategy_->start(oss_);
    for (auto &item : items) {
      listStrategy_->addListItem(oss_, item);
    }
    listStrategy_->end(oss_);
  }

  void set_output_format(const OutputFormat format) {
    switch (format) {
    case OutputFormat::Markdown:
      listStrategy_ = std::make_unique<MarkdownListStrategy>();
      break;
    case OutputFormat::Html:
      listStrategy_ = std::make_unique<HtmlListStrategy>();
      break;
    default:
      throw std::invalid_argument("Unsupported strategy.");
    }
  }

  std::string str() const { return oss_.str(); }

private:
  std::ostringstream oss_;
  std::unique_ptr<ListStrategy> listStrategy_;
};

int main() {
  // markdown
  TextProcessor tp;
  tp.set_output_format(OutputFormat::Markdown);
  tp.appendList({"foo", "bar", "baz"});
  std::cout << tp.str() << '\n';

  // html
  tp.clear();
  tp.set_output_format(OutputFormat::Html);
  tp.appendList({"foo", "bar", "baz"});
  std::cout << tp.str() << '\n';

  return 0;
}
