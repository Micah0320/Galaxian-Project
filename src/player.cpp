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

Image Player::you_("images/sw/swXWing.gif");
Sound Player::explode_("sounds/explosion.wav");
void Player::Draw()
{
    if (alive && lives_ > 0)
    {
        surface_.put_image(you_, rect_);
    }
}

void Player::move()
{
    KeyPressed keypressed = get_keypressed();
    if (keypressed[LEFTARROW])
    {
        rect_.x -= speed_;
    }

    if (keypressed[RIGHTARROW])
    {
        rect_.x += speed_;
    }
    
    if (rect_.x + rect_.w >= 640)
    {
        rect_.x = 640 - rect_.w;
    }
    
    if (rect_.x <= 0)
    {
        rect_.x = 0;
    }
        
}

void Player::DetectCollision(Laser & laser)
{
    double corner2x = rect_.x + rect_.w;
    double corner2y = rect_.y + rect_.h;

    double corner1x = laser.x() + laser.w();
    double corner1y = laser.y() + laser.h();

    if ((laser.x() > rect_.x && laser.x() < corner2x) && (laser.y() < corner2y && corner2y < corner1y) && alive)
    {
        alive = 0;
        laser.isAlive() = 0;
        die();
        int center_x = rect_.x + (rect_.w / 2);
        int center_y = rect_.y + (rect_.h / 2);
        int r = 2;
        laser.playSound();
        for (int i = 0; i < 50; ++i)
        {
            surface_.put_circle(center_x, center_y, r, 254, 4, 4);
            surface_.put_circle(center_x, center_y, r / 2, 232, 215, 8);
            if (i % 2 == 0)
                ++r;
        }
        return;
    }
    if ((rect_.x < laser.x() && laser.x() < corner2x) && (laser.y() < rect_.y && rect_.y < corner1y) && alive)
    {
        alive = 0;
        laser.isAlive() = 0;
        die();
        int center_x = rect_.x + (rect_.w / 2);
        int center_y = rect_.y + (rect_.h / 2);
        int r = 2;
        laser.playSound();
        for (int i = 0; i < 50; ++i)
        {
            surface_.put_circle(center_x, center_y, r, 254, 4, 4);
            surface_.put_circle(center_x, center_y, r / 2, 232, 215, 8);
            if (i % 2 == 0)
                ++r;
        }
        return;
    }
    return;
}

/*void DetectCollision(Alien & alien)
{
    double corner2x = rect_.x + rect_.w;
    double corner2y = rect_.y + rect_.h;

    double corner1x = alien.x() + alien.w();
    double corner1y = alien.y() + alien.h();

    if ((alien.x() > rect_.x && alien.x() < corner2x) && (alien.y() < corner2y && corner2y < corner1y) && alive)
    {
        alive = 0;
        alien.isAlive() = 0;
        die();
        int center_x = rect_.x + (rect_.w / 2);
        int center_y = rect_.y + (rect_.h / 2);
        int r = 2;
        for (int i = 0; i < 50; ++i)
        {
            surface_.put_circle(center_x, center_y, r, 254, 4, 4);
            surface_.put_circle(center_x, center_y, r / 2, 232, 215, 8);
            if (i % 2 == 0)
                ++r;
        }
        return;
    }
    if ((rect_.x < alien.x() && alien.x() < corner2x) && (alien.y() < rect_.y && rect_.y < corner1y) && alive)
    {
        alive = 0;
        alien.isAlive() = 0;
        die();
        int center_x = rect_.x + (rect_.w / 2);
        int center_y = rect_.y + (rect_.h / 2);
        int r = 2;
        for (int i = 0; i < 50; ++i)
        {
            surface_.put_circle(center_x, center_y, r, 254, 4, 4);
            surface_.put_circle(center_x, center_y, r / 2, 232, 215, 8);
            if (i % 2 == 0)
                ++r;
        }
        return;
    }
    return;
    }*/
