#include "explosion.h"

Sound Explosion::sound("sounds/explosion.wav");

void Explosion::explode(int x, int y)
{
    center.x += x + 16;
    center.y += y + 16;

    up.x = center.x;
    up.y = center.y - h_;

    down.x = center.x;
    down.y = center.y + h_;

    left.x = center.x - w_;
    left.y = center.y;

    right.x = center.x + w_;
    right.y = center.y;

    leftup.x = center.x - w_;
    leftup.y = center.y - h_;

    rightup.x = center.x + w_;
    rightup.y = center.y - h_;
   
    leftdown.x = center.x - w_;
    leftdown.y = center.y + h_;
    
    rightdown.x = center.x + w_;
    rightdown.y = center.y + h_;

    alive_ = true;

    disperse_count = 0;
}

void Explosion::disperse()
{
    if (disperse_count < 10 && alive_)
    {
        leftup.x -= rand () % 3;                            rightup.x += rand() % 3;
        leftup.y -= rand() % 3;     up.y -= rand() % 3;     rightup.y += rand() % 3;
        
        left.x -= rand() % 3;                               right.x += rand() % 3;
        
        leftdown.x -= rand() % 3;                           rightdown.x += rand() % 3;
        leftdown.y += rand() % 3;   down.y += rand() % 3;   rightdown.y += rand() % 3;

        sound.play();
        ++disperse_count;
        //put sound here
    }
}

void Explosion::fall()
{
    if (disperse_count >= 10 && alive_)
    {
        int speed = 3;
        leftup.y += speed;
        up.y += speed;
        rightup.y += speed;
        left.y += speed;
        center.y += speed;
        right.y += speed;
        leftdown.y += speed;
        down.y += speed;
        rightdown.y += speed;

        if (cen_r > 100) --cen_r;
        if (cen_g > 100) --cen_g;
        if (cen_b < 100) ++cen_b;
        if (edg_r > 100) --edg_r;
        if (edg_g > 100) --edg_g;
        if (edg_b < 100) ++edg_b;
        if (cor_r > 100) --cor_r;
        if (cor_g < 100) ++cor_g;
        if (cor_b < 100) ++cor_b;
 
        center_color = {Uint8(cen_r), Uint8(cen_g), Uint8(cen_b), 0};
        edge_color = {Uint8(edg_r), Uint8(edg_g), Uint8(edg_b), 0};
        corner_color = {Uint8(cor_r), Uint8(cor_g), Uint8(cor_b), 0}; 
    }
    
    if (center.y >= H)
    {
        alive_ = false;
        cen_r = 231; cen_g = 228; cen_b = 20;
        edg_r = 255; edg_g = 114; edg_b = 20;
        cor_r = 255; cor_g = 0;   cor_b = 20;
        center.x = 0;
        center.y = 0;
    }
}

void Explosion::draw()
{
    if (alive_)
    {
        surface_.put_rect(leftup, corner_color);
        surface_.put_rect(up, edge_color);
        surface_.put_rect(rightup, corner_color);
        surface_.put_rect(left, edge_color);
        surface_.put_rect(center, center_color);
        surface_.put_rect(right, edge_color);
        surface_.put_rect(leftdown, corner_color);
        surface_.put_rect(down, edge_color);
        surface_.put_rect(rightdown, corner_color);
    }
}

void build_explosion(Surface & surface, std::vector < Explosion > & explosion)
{
    for (int i = 0; i < 30; ++i)
    {
        Explosion explosion_(surface, 0, 0, 4, 4, false);
        explosion.push_back(explosion_);
    }
    explosion.shrink_to_fit();
}

void find_explosion(std::vector < Explosion > & explosion, int x, int y)
{
    for (int i = 0; i < 30; ++i)
    {
        if (!explosion[i].alive())
        {
            explosion[i].explode(x, y);
            break;
        }
    }
}
