#include "Person.hpp"
#include "ChatRoom.hpp"
#include <iostream>
#include <utility>

Person::Person(std::string name)
    : name_(std::move(name))
{}

void Person::say(const std::string& message) const
{
    roomPtr_->broadcast(name_, message);
}

void Person::pm(const std::string& who, const std::string& message) const
{
    roomPtr_->message(name_, who, message);
}

void Person::receive(const std::string& origin, const std::string& message)
{
    std::string s{origin + ": \"" + message + "\""};
    std::cout << "[" << name_ << "'s chat session]" << s << "\n";
    chatLog_.emplace_back(s);
}

bool Person::operator==(const Person& rhs) const
{
    return name_ == rhs.name_;
}

bool Person::operator!=(const Person& rhs) const
{
    return !(rhs == *this);
}
