#ifndef PLAYER_H
#define PLAYER_H
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
#include "laser.h"



class Player
{
public:
Player(Surface & surface, int l = 3)
    :surface_(surface), lives_(l)
    {
        rect_ = you_.getRect();
        rect_.y = surface.h() - 75;
        rect_.x = (surface.w()) / 2 - rect_.w;
    }
    void Draw();
    void move();
    void DetectCollision(Laser & laser);
    int x()
    {return rect_.x;}
    int y()
    {return rect_.y;}
    int w()
    {return rect_.w;}
    int h()
    { return rect_.h;}
    int & score()
    {
        return score_;
    }
    int score() const
    {
        return score_;
    }
    int lives() const
    {return lives_;}
    bool isAlive() const
    {
        return alive;
    }
    bool & isAlive()
    {
        return alive;
    }
    void die()
    {--lives_;
        explode_.play();}
    void revive()
    {
        alive = 1;
        rect_.x = (surface_.w()) / 2 - rect_.w;   
    }
private:
    double speed_ = 4.1;
    Rect rect_;
    static Image you_;
    static Sound explode_;
    Surface surface_;
    bool alive = 1;
    int lives_;
    int score_ = 0;
};
#endif
