#ifndef ALIEN_H
#define ALIEN_H
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
#include "player.h"
#include "laser.h"

//#include "fleet.h"


class Alien
{
public:
Alien(Surface & surface, int n, int s = 25)
    :surface_(surface), pointValue_(s)
    {
        dive = 0;
        ++numAlive;
    }
    
    
    int w() const
    {
        return rect_.w;
    }
    int h()
    {
        return rect_.h;
    }
    int x() const
    {
        return rect_.x;
    }
    int & x()
    {
        return rect_.x;
    }
    int y() const
    {
        return rect_.y;
    }
    bool & Alive()
    {
        return isAlive;
    }
   
    void revive()
    {
        isAlive = 1;
        numAlive += 1;
    }
   
    void Draw();
    void move();
    void DetectCollision(Laser &, int &);
    void speedUpdate()
    {
        speed_ *= -1;
    }
    void die()
    {
        isAlive = 0;
        numAlive -= 1;
    }
    int numberAlive()
    {
        return numAlive;
    }
    void reset(int);
    void attack(std::vector<Laser> &);
    bool getDive()
    {
        return dive;
    }
    int pointValue()
    {
        return pointValue_;
    }
private:
    static int numAlive;
    bool isAlive = 1;
    bool dive;
    int pointValue_;
    double speed_ = 3.1;
    Rect rect_;
    Surface & surface_;
    int start_y;
    int start_x;
    friend class RedAlien;
    friend class BlueAlien;
    friend class PurpleAlien;
    friend class FlagAlien;
    //friend class Fleet;
    
    
};


class RedAlien: public Alien
{
public:
RedAlien(Surface & surface, int n)
    :Alien(surface, n, 100)
    {
        rect_ = red_alien_.getRect();
        rect_.x += rect_.w * n + 2;
        rect_.y = rect_.h + 30;
        start_y = rect_.y;
    }
    
    void Draw();
    
    
private:
    //int pointValue = 25;
    static Image red_alien_;

   
};

class BlueAlien: public Alien
{
public:
BlueAlien(Surface & surface, int n)
    :Alien(surface, n, 25)
    {
        rect_ = blu_alien_.getRect();
        rect_.x = rect_.w * n + 2;
        rect_.y = (rect_.h * 3) + 30;
        start_y = rect_.y;
    }
    
    void Draw();
    
    
private:
    //int pointValue = 50;
    static Image blu_alien_;
   
    
};

class PurpleAlien: public Alien
{
public:
PurpleAlien(Surface & surface, int n)
    :Alien(surface, n, 50)
    {
        rect_ = pur_alien_.getRect();
        rect_.x = rect_.w * n + 2;
        rect_.y = (rect_.h * 2) + 30;
        start_y = rect_.y;
    }
    
    void Draw();
    
    
private:
    //int pointValue = 100;
    static Image pur_alien_;
    
    
};

class FlagAlien: public Alien
{
public:
FlagAlien(Surface & surface, int n)
    :Alien(surface, n, 250)
    {
        rect_ = flag_alien_.getRect();
        if(n == 0)
        {
            rect_.x = (rect_.w * 2) + 2;
           
        }
        else
        {
            rect_.x = (rect_.w * 7) + 2;
        }
        originalx = rect_.x;
        rect_.y = rect_.h;
        start_y = rect_.h;
    }
   
    void Draw();
    void StartPos()
    {
        rect_.x = originalx;
        rect_.y = start_y;
    }
    
    void revive()
    { isAlive = 1;
        ++numAlive;}
    void reset()
    {
        StartPos();
        revive();
    }
        
    
    
private:
    //int pointValue = 250;
    static Image flag_alien_;
    int originalx;
};

#endif
