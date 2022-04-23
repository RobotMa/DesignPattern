#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

#include <boost/iterator/iterator_facade.hpp>
#include <utility>

struct Node
{
    string value_;
    Node*  next_ = nullptr;

    explicit Node(string value)
        : value_(std::move(value))
    {}

    Node(string value, Node* const parent)
        : value_(std::move(value))
    {
        parent->next_ = this;
    }
};

struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag>
{
    Node* current_ = nullptr;

    ListIterator() = default;

    explicit ListIterator(Node* const current)
        : current_(current)
    {}

private:
    friend class boost::iterator_core_access;

    void increment() { current_ = current_->next_; }

    [[nodiscard]] bool equal(const ListIterator& other) const { return other.current_ == current_; };

    [[nodiscard]] Node& dereference() const { return *current_; }
};

int main()
{
    Node alpha{"alpha"};
    Node beta{"beta", &alpha};
    Node gamma{"gamma", &beta};

    for_each(ListIterator{&alpha}, ListIterator{}, [](const Node& n) { cout << n.value_ << endl; });

    getchar();
    return 0;
}
