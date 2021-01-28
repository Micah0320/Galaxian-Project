#ifndef LASER_H
#define LASER_H

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

class Laser
{
public:
Laser(Surface & surface, int r, int g, int b, bool t = 1)
    :surface_(surface), r_(r), g_(g), b_(b), type(t)
    {
        rect_.w = 3;
        rect_.h = 10;
    }
    void fire(int, int);
    //void fire(Alien &);
    void stopFire();
    
    bool isAlive() const
    { return isLive;}
    
    bool & isAlive()
    { return isLive;}
    
    int x()const
    { return rect_.x;}
    int y()const
    { return rect_.y;}
    int w()const
    { return rect_.w;}
    int h()const
    { return rect_.h;}
    
    void move();
    //void move(Alien &);
    void playSound()
    {
        explosion.play();
    }
    void draw();
private:
    bool isLive = 0;
    Rect rect_;
    int r_,g_,b_;
    Surface surface_;
    double speed_ = 6.75;
    bool type;
    static Sound explosion;
    friend class Player;
};
#endif
