#include <iostream>
#include <utility>
#include <vector>

struct GraphicObject
{
    virtual void draw()      = 0;
    virtual ~GraphicObject() = default;
};

struct Circle : GraphicObject
{
    void draw() override { std::cout << "Circle" << std::endl; }
};

struct Group : GraphicObject
{
    std::string name_;

    explicit Group(std::string  name)
        : name_{std::move(name)}
    {}

    void draw() override
    {
        std::cout << "Group " << name_.c_str() << " contains:" << std::endl;
        for (auto&& o : objects)
            o->draw();
    }

    std::vector<GraphicObject*> objects;
};

int main()
{
    Group  root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();

    return 0;
}