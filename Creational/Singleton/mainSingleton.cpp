#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Database {
public:
  virtual int get_population(const std::string &name) = 0;
  virtual ~Database() = default;
};

class SingletonDatabase : public Database {
private:
  SingletonDatabase() {
    std::cout << "Initializing database" << std::endl;

    std::ifstream ifs("capitals.txt");

    std::string s, s2;
    while (getline(ifs, s)) {
      getline(ifs, s2);
      int pop = boost::lexical_cast<int>(s2);
      capitals[s] = pop;
    }
    // instance_count++;
  }

  std::map<std::string, int> capitals;

public:
  // static int instance_count;

  SingletonDatabase(SingletonDatabase const &) = delete;
  void operator=(SingletonDatabase const &) = delete;

  static SingletonDatabase &get() {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const std::string &name) override {
    return capitals[name];
  }

  /*
  static SingletonDatabase* get_instance()
  {
    if (!instance)
      instance = new SingletonDatabase;
    return instance; // atexit
  }
  */
};

// int SingletonDatabase::instance_count = 0;

class DummyDatabase : public Database {
  std::map<std::string, int> capitals;

public:
  DummyDatabase() {
    capitals["alpha"] = 1;
    capitals["beta"] = 2;
    capitals["gamma"] = 3;
  }

  int get_population(const std::string &name) override {
    return capitals[name];
  }
};

struct SingletonRecordFinder {
  int total_population(const std::vector<std::string>& names) {
    int result = 0;
    for (auto &name : names)
      result += SingletonDatabase::get().get_population(name);
    return result;
  }
};

struct ConfigurableRecordFinder {
  explicit ConfigurableRecordFinder(Database &db) : db_{db} {}

  int total_population(const std::vector<std::string>& names) const {
    int result = 0;
    for (auto &name : names)
      result += db_.get_population(name);
    return result;
  }

  Database & db_;
};

int main() {

  const std::string city = "Tokyo";
  std::cout << city << " has a population of "
            << SingletonDatabase::get().get_population(city) << '\n';

  return 0;
}