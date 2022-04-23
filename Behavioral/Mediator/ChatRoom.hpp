#pragma once

#include "Person.hpp"

#include <algorithm>
#include <memory>
#include <vector>

struct ChatRoom : std::enable_shared_from_this<ChatRoom>
{
    std::vector<Person*> people_;

    void join(Person* p)
    {
        std::string join_msg = p->name_ + " joins the chat";
        broadcast("room", join_msg);
        p->roomPtr_ = shared_from_this();
        people_.push_back(p);
    }

    void broadcast(const std::string& origin, const std::string& message) const
    {
        for (auto p : people_)
            if (p->name_ != origin)
                p->receive(origin, message);
    }

    void message(const std::string& origin, const std::string& who, const std::string& message)
    {
        auto target = std::find_if(begin(people_), end(people_), [&who](const Person* p) { return p->name_ == who; });
        if (target != end(people_)) {
            (*target)->receive(origin, message);
        }
    }
};
