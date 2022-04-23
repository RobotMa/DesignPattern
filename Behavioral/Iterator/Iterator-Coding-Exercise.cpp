#include <iostream>
#include <vector>

#include <gtest/gtest.h>

using namespace std;

template<typename T>
struct Node
{
    T     value_;
    Node *left_{nullptr}, *right_{nullptr}, *parent_{nullptr};

    explicit Node(T value)
        : value_(value)
    {}

    Node(T value, Node<T>* left, Node<T>* right)
        : value_(value)
        , left_(left)
        , right_(right)
    {
        left->parent_ = right->parent_ = this;
    }

    void preorder_traversal_impl(Node<T>* current, vector<Node<T>*>& result)
    {
        result.push_back(current);
        if (current->left_) {
            preorder_traversal_impl(current->left_, result);
        }
        if (current->right_) {
            preorder_traversal_impl(current->right_, result);
        }
    }

    // traverse the node and its children_ preorder
    // and put all the results into `result`
    void preorder_traversal(vector<Node<T>*>& result) { preorder_traversal_impl(this, result); }
};


namespace {

class Evaluate : public ::testing::Test
{};

TEST_F(Evaluate, ExampleTest)
{
    /*
     *       a
     *      / \
     *     b   e
     *    / \
     *   c  d
     */
    Node<char> c{'c'};
    Node<char> d{'d'};
    Node<char> e{'e'};
    Node<char> b{'b', &c, &d};
    Node<char> a{'a', &b, &e};

    vector<Node<char>*> result;
    a.preorder_traversal(result);

    ostringstream oss;
    for (auto n : result){
        oss << n->value_;
    }
    ASSERT_EQ("abcde", oss.str());

    vector<Node<char>*> result2;
    b.preorder_traversal(result2);

    ostringstream oss2;
    for (auto n : result2){
        oss2 << n->value_;
    }
    ASSERT_EQ("bcd", oss2.str());
}

} // namespace

int main(int ac, char* av[])
{
    //::testing::GTEST_FLAG(catch_exceptions) = false;
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}