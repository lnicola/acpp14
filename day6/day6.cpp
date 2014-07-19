#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class shape
{
public:
    string name_;

    shape(string name)
        : name_(name)
    {
        cout << "shape()" << endl;
    }

    virtual ~shape()
    {
        cout << "~shape()" << endl;
    }

    virtual void draw() const = 0;
};

class circle : public shape
{
public:
    int x_, y_, r_;

    circle(string name, int x, int y, int r)
        : shape(name), x_(x), y_(y), r_(r)
    {
        cout << "circle()" << endl;
    }

    ~circle()
    {
        cout << "~circle()" << endl;
    }

    void draw() const override
    {
        cout << "circle at (" << x_ << ", " << y_ << ")" << endl;
    }
};

class rectangle : public shape
{
public:
    rectangle(string name)
        : shape(name)
    {
    }

    void draw() const override
    {
        cout << "dreptunghi" << endl;
    }
};

int main()
{
    //circle c;

    //cout << c.x_ << endl;

    //c.draw();

    //shape *s = &c;
    //s->draw();

    //shape *r = new rectangle("dreptunghi");
    
    //auto p = new int[10];
    //auto p2 = unique_ptr<int []>(p);

    ////auto arr = make_unique<int []>(10);
    //auto arr2 = unique_ptr<int []>(new int[10]);

    vector<unique_ptr<shape>> shapes;
    shapes.push_back(make_unique<circle>("cerc 1", 1, 2, 3));
    shapes.push_back(make_unique<rectangle>("dreptunghi"));

    //vector<shape *> sp;
    //for (shape * const &p : sp)
    //    ;

    for (const auto &s : shapes)
        s->draw();

    shape *s2 = new circle("x", 1, 2, 3);
    delete s2;
    
    //int x[n];

    //auto f = [](auto x, auto y) { return x + y; };
    //f(2, 3);
    //f(string("a"), string("b"));
    //auto s = "xhg"s;

    //ostream o;
    //ofstream ofs("x");
}
