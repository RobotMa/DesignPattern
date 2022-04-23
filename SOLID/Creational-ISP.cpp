#include <iostream>
#include <string>

// Interface sgregation principle

struct Document
{
    std::string name;
};

// struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
// struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

struct IPrinter
{
    virtual void print(Document& doc) = 0;
    virtual ~IPrinter()               = default;
};

struct IScanner
{
    virtual void scan(Document& doc) = 0;
    virtual ~IScanner()              = default;
};

struct Printer : IPrinter
{
    // TODO: need to revisit on what this print function is for
    void print(Document& doc) override { std::cout << doc.name << '\n'; };
};

struct Scanner : IScanner
{
    // TODO: need to revisit on what this scan function is for
    void scan(Document& doc) override { std::cout << doc.name << '\n'; };
};

struct IMachine
    : IPrinter
    , IScanner
{};

struct Machine : IMachine
{
    IPrinter& mPrinter;
    IScanner& mScanner;

    Machine(IPrinter& printer, IScanner& scanner)
        : mPrinter{printer}
        , mScanner{scanner}
    {}

    void print(Document& doc) override { mPrinter.print(doc); }
    void scan(Document& doc) override { mScanner.scan(doc); };
};

// IPrinter --> Printer
// everything --> Machine

int main()
{
    const Document doc{"title"};
    Printer        printer;
    Scanner        scanner;
    Machine        machine(printer, scanner);

    return 0;
}