#include "stdafx.h"

using namespace ci;
using namespace ci::app;
using namespace ci::cairo;
using namespace ci::gl;
using namespace std;

struct vec2f
{
    double x;
    double y;

    vec2f()
        : x(), y()
    {
    }

    vec2f(double x, double y)
        : x(x), y(y)
    {
    }

    vec2f & operator+=(const vec2f &other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }
};

vec2f operator+(vec2f v1, const vec2f &v2)
{
    return v1 += v2;
}

vec2f operator*(double a, const vec2f &v)
{
    return vec2f(a * v.x, a * v.y);
}

ostream & operator<<(ostream &o, const vec2f &v)
{
    return o << '(' << v.x << ", " << v.y << ')';
}

class output_context
{
public:
    virtual void line(vec2f p1, vec2f p2) = 0;
};

class svg_output_context : public output_context
{
    ostream &stream_;

public:
    svg_output_context(ostream &stream)
        : stream_(stream)
    {
        stream_ << "<svg height='2000' width='2000' style='stroke: rgb(255,0,0); stroke-width: 2'>" << endl;
    }

    ~svg_output_context()
    {
        stream_ << "</svg>" << endl;
    }

    void line(vec2f p1, vec2f p2)
    {
        stream_ << "<line x1='" << p1.x << "' y1='" << p1.y << "' x2='" << p2.x << "' y2='" << p2.y << "' />" << endl;
    }
};

class cairo_display_context : public output_context
{
public:
    Context &ctx_;

    cairo_display_context(Context &ctx)
        : ctx_(ctx)
    {
    }

    void line(vec2f p1, vec2f p2)
    {
        ctx_.line(Vec2f(p1.x, p1.y), Vec2f(p2.x, p2.y));
    }
};

class turtle
{
    vec2f position_;
    double angle_;
    output_context &ctx_;

public:
    turtle(output_context &ctx)
        : position_(), angle_(), ctx_(ctx)
    {
    }

    turtle(output_context &ctx, vec2f position)
        : position_(position), angle_(), ctx_(ctx)
    {
    }

    void forward(double step)
    {
        vec2f old_position = position_;
        position_ += step * vec2f(cos(angle_), sin(angle_));

        ctx_.line(old_position, position_);
    }

    void left(double angle)
    {
        angle_ += angle;
    }

    void right(double angle)
    {
        angle_ -= angle;
    }
};

const double pi = 3.1415926535897932384626433832795;

class l_system
{
public:
    map<char, string> rules;
    double d;
    double a;
    turtle t;

    l_system(output_context &ctx, vec2f position)
        : t(ctx, position)
    {
        rules['F'] = "FF+F+F+F+FF";
        d = 10;
        a = pi / 2;
    }

    void run(int depth, const string &input)
    {
        for (char c : input)
        {
            if (c == '+')
                t.left(a);
            else if (c == '-')
                t.right(a);
            else if (c == 'F')
            {
                if (depth > 1)
                    run(depth - 1, rules[c]);
                else
                    t.forward(d);
            }
            else
                __debugbreak();
        }
    }
};

class CairoBasicApp : public AppBasic
{
    unique_ptr<SurfaceImage> surface_image_;
  
    void paint(Context ctx)
    {
        ctx.setLineCap(LINE_CAP_SQUARE);

        cairo_display_context cd(ctx);
        
        ofstream file("foo.html");
        svg_output_context csvg(file);

        l_system ls(csvg, vec2f(0, 0));
        ctx.setSourceRgb(1, 1, 1);
        ls.run(5, "F+F+F+F");
        ctx.stroke();
    }

    void draw() override
    {
        gl::draw(Texture(surface_image_->getSurface()));
    }

    void keyDown(KeyEvent event) override
    {
        if (event.getChar() == KeyEvent::KEY_ESCAPE ||
            event.isAltDown() && event.getCode() == KeyEvent::KEY_F4)
            quit();
    }

    void resize() override
    {
        surface_image_.reset(new SurfaceImage(getWindowWidth(), getWindowHeight()));

        paint(*surface_image_);
    }

    void prepareSettings(Settings *settings) override
    {
        settings->setFullScreen();
    }
};

CINDER_APP_BASIC(CairoBasicApp, RendererGl)
