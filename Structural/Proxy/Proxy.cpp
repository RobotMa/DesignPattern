#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <cpprest/filestream.h>
#include <cpprest/http_client.h>

using namespace std;

struct BankAccount
{
    virtual ~BankAccount()            = default;
    virtual void deposit(int amount)  = 0;
    virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount // checking
{
    explicit CurrentAccount(const int balance)
        : balance_(balance)
    {}

    void deposit(int amount) override { balance_ += amount; }

    void withdraw(int amount) override
    {
        if (amount <= balance_)
            balance_ -= amount;
    }

    friend ostream& operator<<(ostream& os, const CurrentAccount& obj) { return os << "balance_: " << obj.balance_; }

private:
    int balance_;
};

struct Image
{
    virtual ~Image()    = default;
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    explicit Bitmap(const string& filename) { cout << "Loading image from " << filename << endl; }

    void draw() override { cout << "Drawing image" << endl; }
};

struct LazyBitmap : Image
{
    explicit LazyBitmap(string filename)
        : filename_(std::move(filename))
    {}

    void draw() override
    {
        if (bmp == nullptr)
            bmp = std::make_unique<Bitmap>(filename_);
        bmp->draw();
    }

private:
    std::unique_ptr<Bitmap> bmp{nullptr};
    string                  filename_;
};

void draw_image(Image& img)
{
    cout << "About to draw the image" << endl;
    img.draw();
    cout << "Done drawing the image" << endl;
}

void virtual_proxy()
{
    LazyBitmap img{"pokemon.png"};
    draw_image(img); // loaded whether the bitmap is loaded or not
    draw_image(img);
}

void smart_pointers()
{
    BankAccount* a = new CurrentAccount(123);
    a->deposit(321);
    delete a;

    // << will not work if you make this a shared_ptr<BankAccount>
    auto b = make_shared<CurrentAccount>(123);

    BankAccount* actual = b.get(); // pointer's own operations on a .
    (void)actual;
    b->deposit(321); // underlying object's operations are on ->
                     // note this expression is identical to what's above
    cout << *b << endl;
    // no delete

    // see shared_ptr in file structure window
}

// TODO : Communication proxy is initially run on Windows, currently having runtime error
struct Pingable
{
    virtual ~Pingable()                        = default;
    virtual string ping(const string& message) = 0;
};

struct Pong : Pingable
{
    string ping(const string& message) override { return message + " pong"; }
};

struct RemotePong : Pingable
{
    string ping(const string& message) override
    {
        web::http::client::http_client client(U("http://localhost:9149/"));
        web::uri_builder               builder(U("/api/pingpong/"));
        builder.append(message);
        pplx::task<string> task =
          client.request(web::http::methods::GET, builder.to_string()).then([=](const web::http::http_response& r) {
              return r.extract_string();
          });
        task.wait();
        return task.get();
    }
};

void tryIt(Pingable& pp)
{
    cout << pp.ping("ping") << "\n";
}

void communication_proxy()
{
    Pong pp;
    for (int i = 0; i < 3; ++i) {
        tryIt(pp);
    }

    // RemotePing (Communication Proxy)
    RemotePong rp;
    for (int i = 0; i < 3; ++i) {
        tryIt(rp);
    }
}

// ======== Property Proxy ======================

template<typename T>
struct Property
{
    T value;
    explicit Property(const T initialValue) { *this = initialValue; }
      operator T() { return value; }
    T operator=(T newValue) { return value = newValue; }
};

// ===========================================

struct Creature
{
    // TODO : why does this make sense again?
    Property<int>    strength{10};
    Property<int>    agility{5};
    Property<double> life{0.5};
};

void property_proxy()
{
    Creature creature;
    creature.agility = 20;

    cout << creature.strength << '\n';
    cout << creature.agility << '\n';
    cout << creature.life << '\n';
}

int main()
{
    property_proxy();
    smart_pointers();
    virtual_proxy();
    communication_proxy();

    getchar();
    return 0;
}
