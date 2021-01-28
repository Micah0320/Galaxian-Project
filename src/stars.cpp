#include <iostream>
#include "stars.h"
#include "Surface.h"

void Galaxy::draw()
{
    for (int i = 0; i < 75; ++i)
    {
        if (stars[i].y() >= H - 51)
        {
            stars[i].y(0);
            stars[i].x(rand() % W);
        }
        stars[i].move();
        surface_.put_rect(stars[i].x(), stars[i].y(), stars[i].w(), stars[i].h(),
                          stars[i].r(), stars[i].g(), stars[i].b());
    }
}

void Galaxy::build()
{
    for (int i = 0; i < 75; ++i)
    {
        Stars star;
        
        star.x(rand() % W);
        star.y(rand() % (H - 51));

        star.type(rand() % 2 + 1);
        
        if (star.type() == 1)
        {
            star.w(3);
            star.h(3);
            star.speed(2);
            star.r(185);
            star.g(235);
            star.b(8);
        }
        else if (star.type() == 2)
        {
            star.w(2);
            star.h(2);
            star.speed(1);
            star.r(0);
            star.g(113);
            star.b(220);
        }
        stars.push_back(star);
    }
    stars.shrink_to_fit();
}

void Stars::move()
{
    y_ += speed_;
}
