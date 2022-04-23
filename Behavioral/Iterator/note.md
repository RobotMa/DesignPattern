# Overview
A class that faciliates the traversal
- keeps a reference (pointer) to the current element
- moves to a different element

Implicit usage
- Range-based for
- Coroutines

# Iterators in STL
Very simple demo to show how to use iterator with vector
- Global functions std::begin(), std::end() v.s. member functions 
    - std::vector::begin(), std::vector::end()
    - for array, you have to use the global functions
    
- reverse iterator only applicable for some containers such as vector with rbegin
    - Note : still use ++ to advance the iterator
    
- introduce vector<>::const_reverse_iterator with crbegin()
    - Note : no range based for loop for reverse iterator
    
- const iterator means that you can't modify the value_ pointed by the iterator
    
- No reverse range for loop
 
- Qualification for using ranged based for loop
    - Need to implement begin() and end() operators
    - Outdated boolean in range based for loop
        - Need to use `for (auto&& name : names)`
            - Can bind to both lvalue and rvalue, essentially, it is universal reference.
            - How do we guarantee the constness here? 
        - auto&& is the safest approach to go
            - why safety? 

# Binary Tree Iterator
templated implementation of a binary tree
- The node also points back to its parent_ node
- Every node contains the pointer to the root node `BinaryTree<T>*`
- Initialization of a template variable 
    - `T value_ = T();`
- TODO : why have a set_tree function?
    - It enforces all nodes to point to the same BinaryTree
    - But why is this needed?
- Not using the smart pointer -> need to delete nodes in desctrucotr -> assume the parent_ (current) node owns all of its children_ nodes
- Iterator 
    - Need to define not equal operator : `bool operator!=(const PreOrderIterator<U>& iter)``
    - Need to define plus plus operator :  `PreOrderIterator<U>& operator++()`
    - Need to define `begin()` and `end()` operators/functions
- Why define and construct the `pre_order_traversal` class?    

# Tree Iterator with Coroutines
Explain why `PreOrderIterator<U>& operator++()` is very complex : can't do simple recursive here
Use coroutine to write a reverse iterator
- [coroutine](https://theboostcpplibraries.com/boost.coroutine) : originally a feature from other languages
- generator : where can I see the documentation?
- co_yield : some people say this can lead to longer runtime.
    - In these programming languages, yield can be used like return. However, when yield is used, the function remembers the location, and if the function is called again, execution continues from that location. 
    - Traversing the left_ elements and returning them in some kind of suspending [mechanism](mechanism) 

# Boost Iterator [Facade](https://www.udemy.com/course/patterns-cplusplus/learn/lecture/7960406?components=buy_button%2Cdiscount_expiration%2Cgift_this_course%2Cpurchase%2Cdeal_badge%2Credeem_coupon#questionsi)
Help build iterators for your particular type.
Recap on Facade:
    "Provides a simple, easy to understand user interface over a large and sophistaed body of code"
    
A base class to add to an iterator to quickly define the operations that make up the iterator.
- Use singly linked list as an exmaple
- CRTP !!! `struct ListIterator : boost::iterator_facade<ListIterator, Node, boost::forward_traversal_tag>`
- why? `friend class boost::iterator_core_access`
- wth? `increment()` function is not virtual override, it's not mandate, but will use it if provided.  

# Summary

