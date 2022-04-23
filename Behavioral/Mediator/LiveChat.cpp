#include "ChatRoom.hpp"
#include "Person.hpp"

int main()
{
    auto chatRoomPtr = std::make_shared<ChatRoom>();

    Person john{"John"};
    Person jane{"Jane"};
    chatRoomPtr->join(&john);
    chatRoomPtr->join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon{"Simon"};
    chatRoomPtr->join(&simon);
    simon.say("hi everyone!");

    jane.pm("Simon", "glad you found us, simon!");

    return 0;
}