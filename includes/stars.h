#ifndef STARS_H
#define STARS_H

#include <vector>
#include "Surface.h"
#include "Constants.h"


class Stars
{
public:
Stars(int x = 0, int y = 0, int w = 1, int h = 1, int type = 1, int speed = 1,
      int r = 0, int g = 0, int b = 0)
    :x_(x), y_(y), w_(w), h_(h), type_(type), speed_(speed), r_(r), g_(g), b_(b)
    {}
    
    int x() const
    {
        return x_;
    }
    int y() const
    {
        return y_;
    }
    int w() const
    {
        return w_;
    }
    int h() const
    {
        return h_;
    }
    int r() const
    {
        return r_;
    }
    int g() const
    {
        return g_;
    }
    int b() const
    {
        return b_;
    }
    int type() const
    {
        return type_;
    }
    int speed() const
    {
        return speed_;
    }

    void x(int x)
    {
        x_ = x;
    }
    void y(int y)
    {
        y_ = y;
    }
    void h(int h)
    {
        h_ = h;
    }
    void w(int w)
    {
        w_ = w;
    }
    void r(int r)
    {
        r_ = r;
    }
    void g(int g)
    {
        g_ = g;
    }
    void b(int b)
    {
        b_ = b;
    }
    void type(int type)
    {
        type_ = type;
    }
    void speed(int speed)
    {
        speed_ = speed;
    }

    void move();
    
private:
    int x_, y_, w_, h_;
    int r_, b_, g_;
    int type_;
    int speed_;
        
};


class Galaxy
{
public:
Galaxy(Surface & surface) : surface_(surface)
    {}

    void draw();
    void build();
    
private:
    Surface & surface_;

    std::vector < Stars > stars;
};
#endif
