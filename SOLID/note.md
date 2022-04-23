SOLID Design Principle

# Single Responsibility Principle
A.K.A.: Separation of concern. 

To design a journal system, we need to separate the responsibilities of creation and saving.
Hence, we delegate the saving functionality to a persistence manager.

## Note
### boost::lexical_cast 
Used here that is an alternative to functions like
* std::stoi()
* std::stod()
* std::to_string()

### Pre-increment and Post-increment operators
```
class Point
{
    public:
        Point& operator++();
        Point operator++(int);
};

```

# Open-Closed Principle
Open for extension, closed for modification

## Enterprise pattern (Specification Pattern)
Used frequently in the Domain Driven Design (DDD)


# Liskov Substitution Principle 
Sub types should be immediately substitutable by their base types.

# Interface Segregation Principle

Used decorator pattern as part of an example.

# Dependency Inversion Principle
1. High level modules should not depend on low level modules. They should both depend on the abstract interface.
2. Abstractions should not depend on details. Details should depend on abstractions.

Tricks performed:
1. Based on SRP, put more functionalities in the lower level class
2. Define an abstract interface for the higher level class to inherit from.

Note:
'''
for (auto&& element : vector)
'''
is used in a lot of places. 

Based on "Effecitve Modern C++ 2014", "Item 24 : Distinguish Universal References from Rvalue References" 

The && is a univeral reference. which means that element can bind to either lvalue or rvalue.
Note that `const auto&& element : vector` will make element an rvalue reference due to the presence of the `const` qualifier.
