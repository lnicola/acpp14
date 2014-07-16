#include <iostream>
#include <memory>
#include <utility>

using namespace std;

class trace
{
public:
    trace()
    {
        cout << "ctor trace" << endl;
    }

    ~trace()
    {
        cout << "dtor trace" << endl;
    }
};

class box
{
private:
    unique_ptr<int> x_;

public:
    box()
        : x_(new int(0))
    {
    }

    box(int x)
        : x_(new int(x))
    {
        cout << "ctor " << *x_ << endl;
    }

    box(const box &other) = delete;
    /*
    box(const box &other)
        : x_(new int(*other.x_))
    {
        cout << "copy ctor " << *x_ << endl;
    }
    */

    box(box &&other)
        : x_(move(other.x_))
    {
        cout << "move ctor " << *x_ << endl;
    }
    
    box & operator=(const box &other) = delete;
    /*
    box & operator=(const box &other)
    {
        *x_ = *other.x_;
        cout << "op= " << *x_ << endl;

        return *this;
    }

    */
    box & operator=(box &&other)
    {
        x_ = move(other.x_);

        cout << "move op= " << *x_ << endl;

        return *this;
    }

    ~box()
    {
        if (x_)
            cout << "dtor " << *x_ << endl;
        else
            cout << "dtor empty box" << endl;
    }
};

/*
unique_ptr<trace> make_int()
{
    return make_unique<trace>();
}

unique_ptr<trace> use_int(unique_ptr<trace> p)
{
    cout << "use_int" << endl;
    return p;
}
*/

trace get_trace()
{
    return trace();
}

void f(const trace &t)
{
    cout << "f1" << endl;
}

void f(trace &&t)
{
    cout << "f2" << endl;
}

box get_box(int x)
{
    return box(x);
}

int main()
{
    //box b1(5);
    //box b2 = move(b1);
    
    box &&b3 = get_box(1);

    //{
    //    box b1(4);
    //    box b2(b1);
    //}

    cout << "sfarsitul functiei" << endl;
}
