# Overview
Not necessarily a design pattern, but a computer science branch dealing with how to write parsers.
The underlying knowledge is too broad to cover here.

Applications
- Programming language compilers
- static analysis as in IDEs

Challenges
- Turn strings/text_ into object oriented programming based structures.

## Lexing
Def. Take the input and separate it into different tokens_.
- Goal : Parse and evaluate numerical expressions.
- Step 1 : Define Token struct
    1. enumerate the types needed 
    2. keep the text_ as well for the `integer` type.
- Step 2 : Define the lex function
    1. To find self-contained tokens_
        - simple for parenthesis and addition & substraction
        - for numbers, create a oss buffer : using both the global index i and local index j
    2. Push back to `vector<Token>`

## Parsing
Take the sequence of tokens_ and interpret them into a meaningful object oriented language.
- Goal : Build an expression that we can evaluate.
`struct Element` uses the visitor pattern. It's used for evaluation.
- Step 1 : `struct Integer : Element` 
- Step 2 : `struct BinaryOperation : Element`
- Step 3 :  `shared_ptr<Element> parse()` needs to take care of the parenthesis in this `BinaryOperation`
    - different cases for all tokens_ but `Token::rparen`
    - for `Token::lparen`, ignore nested brackets. Some detailed implementation, can probably ignore.

## Parsers Using Boost
A real life project of designing a programming language of your own. The methodology here should apply to both [compiler language and interpreted language](
https://www.geeksforgeeks.org/difference-between-compiled-and-interpreted-language/).

Note: I feel like this is a showoff of the author because it involves too much background knowledge.

- Use the library Boost::Spirit

1. Abstract Syntax Tree ([AST](https://en.wikipedia.org/wiki/Abstract_syntax_tree)) 
    - Using the [visitor pattern](https://confluence.ci.motional.com/confluence/display/NUCORE/Double+Dispatch+and+the+Visitor+Pattern)
    - all the ast elements are somehow adapted by the Boost::Fusion library
    - Something happened to boost fusion (heterogeneous container)
2. Parser
    - spirit::qi::grammar
    - spirit::qi::rule
    - Backus normal form ([BNF](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form))
    - Visitor can visitor boost::variant<function_body, property, function_signature>
    
3. Printer
    - visitor pattern
        - I see the visit function, but where is the accept function? Need to go over the visitor pattern video as well.
        
4. No specific lexing here, things seem to be handled behind the scene by the framework that the author uses.
    

# Summary
Two stages
1. Lexing
2. Parsing : turn into object oriented constructs

