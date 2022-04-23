#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <boost/lexical_cast.hpp>

// Single responsibility principle

using namespace std;

class Journal
{
private:
  string title_;
  vector<string> entries_;

public:
  explicit Journal(string  title)
    : title_{std::move(title)}
  {
  }

  void add(const string& entry);

  [[nodiscard]] const vector<string>& get() const;
};

void Journal::add(const string& entry)
{
  static int count = 1;
  entries_.push_back(boost::lexical_cast<string>(count++)
    + ": " + entry);
}

const vector<string>& Journal::get() const
{
  return entries_;
}

struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (const auto& s : j.get())
      ofs << s << endl;
  }
};

int main()
{
  Journal journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

  PersistenceManager::save(journal, "diary.txt");

  return 0;
}