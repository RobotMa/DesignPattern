﻿#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details.
//    Details should depend on abstractions.

enum class Relationship : uint8_t
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

struct RelationshipBrowser
{
    virtual vector<Person> find_all_children_of(const string& name) = 0;
    virtual ~RelationshipBrowser()                                  = default;
};

struct Relationships : RelationshipBrowser // low-level
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child)
    {
        relations.emplace_back(parent, Relationship::parent, child);
        relations.emplace_back(child, Relationship::child, parent);
    }

    vector<Person> find_all_children_of(const string& name) override
    {
        vector<Person> result;
        for (auto&& [first, rel, second] : relations) {
            if (first.name == name && rel == Relationship::parent) {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research // high-level
{
    explicit Research(RelationshipBrowser& browser)
    {
        for (auto& child : browser.find_all_children_of("John")) {
            cout << "John has a child called " << child.name << endl;
        }
    }
    //  Research(const Relationships& relationships)
    //  {
    //    auto& relations = relationships.relations;
    //    for (auto&& [first, rel, second_] : relations)
    //    {
    //      if (first.name == "John" && rel == Relationship::parent_)
    //      {
    //        cout << "John has a child called " << second_.name << endl;
    //      }
    //    }
    //  }
};

int main()
{
    Person parent{"John"};
    Person child1{"Chris"};
    Person child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research research(relationships);

    (void) research;

    return 0;
}