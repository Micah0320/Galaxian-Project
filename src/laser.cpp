
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "alien.h"
#include "player.h"
#include "laser.h"
Sound Laser::explosion("sounds/explosion.wav");
void Laser::fire(int x, int y)
{
        isLive = 1;
        rect_.x = x;
        rect_.y = y;
    
}

void Laser::move()
{
    if (type)
        rect_.y -= speed_;
    else
        rect_.y += speed_;
}

void Laser::draw()
{
    if (isLive)
        surface_.put_rect(rect_.x, rect_.y, rect_.w, rect_.h, r_, g_, b_);
}

void Laser::stopFire()
{
    isLive = 0;
}
