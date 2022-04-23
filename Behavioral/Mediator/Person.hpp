#pragma once
#include <memory>
#include <string>
#include <vector>

struct ChatRoom;

struct Person
{
    std::string               name_;
    std::shared_ptr<ChatRoom> roomPtr_{nullptr};
    std::vector<std::string>  chatLog_;

    explicit Person(std::string  name);

    void say(const std::string& message) const;

    void pm(const std::string& who, const std::string& message) const;

    void receive(const std::string& origin, const std::string& message);

    bool operator==(const Person& rhs) const;

    bool operator!=(const Person& rhs) const;
};
