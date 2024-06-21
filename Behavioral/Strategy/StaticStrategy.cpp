#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum class OutputFormat { Markdown, Html };

struct ListStrategy {
  virtual ~ListStrategy() = default;
  virtual void addListItem(ostringstream &oss, const string &item) = 0;
  virtual void start(ostringstream &oss) = 0;
  virtual void end(ostringstream &oss) = 0;
};

struct MarkdownListStrategy : ListStrategy {
  void start(ostringstream &oss) override { (void)oss; }

  void end(ostringstream &oss) override { (void)oss; }

  void addListItem(ostringstream &oss, const string &item) override {
    oss << " * " << item << endl;
  }
};

struct HtmlListStrategy : ListStrategy {
  void start(ostringstream &oss) override { oss << "<ul>" << endl; }

  void end(ostringstream &oss) override { oss << "</ul>" << endl; }

  void addListItem(ostringstream &oss, const string &item) override {
    oss << "<li>" << item << "</li>" << endl;
  }
};

template <typename LS> struct TextProcessor {
  void clear() {
    oss_.str("");
    oss_.clear();
  }

  void appendList(const vector<string> &items) {
    listStrategy_.start(oss_);
    for (const auto &item : items) {
      listStrategy_.addListItem(oss_, item);
    }
    listStrategy_.end(oss_);
  }

  string str() const { return oss_.str(); }

private:
  ostringstream oss_;
  LS listStrategy_;
};

int main() {
  // markdown
  TextProcessor<MarkdownListStrategy> tpm;
  tpm.appendList({"foo", "bar", "baz"});
  cout << tpm.str() << endl;

  // html
  TextProcessor<HtmlListStrategy> tph;
  tph.appendList({"foo", "bar", "baz"});
  cout << tph.str() << endl;

  getchar();
  return 0;
}
