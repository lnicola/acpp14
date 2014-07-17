#include <array>
#include <iostream>
#include <memory>
#include <utility>
#include <tuple>
#include <vector>

using namespace std;

template<typename T>
class box
{
    T x_;

public:

    box()
        : x_()
    {
        cout << "box()" << endl;
    }

    box(T x)
        : x_(x)
    {
        cout << "box(T)" << endl;
    }

    ~box()
    {
        cout << "~box()" << endl;
    }

    /*
    box(const box &other)
    : x_(other.x_)
    {
    }

    box(box &&other)
    : x_(move(other.x_))
    {
    }

    box & operator=(const box &other)
    {
    x_ = other.x_;
    return *this;
    }

    box & operator=(box &&other)
    {
    x_ = move(other.x_);
    return *this;
    }
    */
    const T & get() const
    {
        // const box *this
        // const &int this->x_
        return x_;
    }

    T & get()
    {
        // box *this
        return x_;
    }
};

void print()
{
}

template<typename F, typename... R>
void print(F f, R ...r)
{
    cout << f;
    print(r...);
}

void print_0()
{
}

void print_1(char *t1)
{
    cout << t1;
    print_0();
}

void print_2(int t1, char *t2)
{
    cout << t1;
    print_1(t2);
}

void print_3(int t1, int t2, char *t3)
{
    cout << t1;
    print_2(t2, t3);
}

unique_ptr<int> f(unique_ptr<int> p)
{
    unique_ptr<int> q;
    return q;
    return p;
}

struct foo
{
    void f()
    {
    }
};

int main()
{
    foo f;
    foo() = f;
    const foo f1 = foo();
    const foo &f2 = foo();
    //f2.f();
    foo().f();

    foo &f3 = foo(); // merge in visual studio, dar e gresit


    print(4, 5, "abc");
    cout << endl;
    print_3(4, 5, "abc");

    cout << endl;
    
    int p [] = { 1, 2, 3,
        4, 5, 6,
        7, 8, 9 };
    
    //matrix<int> m(3, p);
    //m[1, 1] == 5;

    // p[col + width * row]

    return 0;
    tuple<int, float> t = make_tuple(2, 3);
    int x = get<0>(t);

    box<int> b1(2);
    cout << b1.get() << endl;
    
    const int n = 7;
    array<int, n> arr1;
    array<int, 7> arr2;
    arr1 = arr2;
    vector<int> v2(7);
    v2[6];

    //box *pb;
    //weak_ptr<box> wp;
    //{
    //    shared_ptr<box> sp2;

    //    {
    //        auto sp = make_shared<box>(10);
    //        sp2 = sp;
    //        wp = sp;
    //        pb = sp.get();
    //    }
    //    // sp2.reset();

    //    cout << sp2->get() << endl;
    //}
    // 

    //shared_ptr<box> sp3 = wp.lock();
    //if (pb)
    //    cout << pb->get() << endl;
    //else
    //    cout << "obiectul a fost distrus" << endl;

    //return 0;

    //box b1(42);
    //const box &b2 = b1;

    //cout << b2.get() << endl;
    //b1.get() = 10;
    //cout << b2.get() << endl;

    ////b2.get_b().val_ = 10;
}
