#include <iostream>

using namespace std;

class point
{
public:
    float x_;
    float y_;

    point()
        : x_(0), y_(0)
    {
    }

    point(float x, float y)
        : x_(x), y_(y)
    {
    }

    point & operator+=(const point &other)
    {
        x_ += other.x_;
        y_ += other.y_;

        return *this;
    }
};

point operator+(point p, const point &other)
{
    p += other;
    return p;
}

ostream & operator<<(ostream &o, const point &p)
{
    return o << '(' << p.x_ << ", " << p.y_ << ')';
}

int main()
{
    point p1;
    point p2(3, 5);
    cout << p1.x_ << endl;
    cout << p2.x_ << endl;
    cout << p2 << ' ' << p2 << endl;

    point p3 = p2;
}
