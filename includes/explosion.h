#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <vector>
#include "Surface.h"
#include "Rect.h"
#include "Color.h"
#include "Constants.h"
#include "Includes.h"
#include "player.h"
#include "alien.h"
class Explosion
{
public:
Explosion(Surface & surface, int x, int y, int w, int h, bool alive)
    :surface_(surface), x_(x), y_(y), w_(w), h_(h), alive_(alive)
    {
        center.x = x + 16;
        center.y = y + 16;
        center.h = h;
        center.w = w;

        up.x = center.x;
        up.y = center.y - h_;
        up.h = h_;
        up.w = w_;

        down.x = center.x;
        down.y = center.y + h_;
        down.h = h_;
        down.w = w_;

        left.x = center.x - w_;
        left.y = center.y;
        left.h = h_;
        left.w = w_;

        right.x = center.x + w_;
        right.y = center.y;
        right.h = h_;
        right.w = w_;

        leftup.x = center.x - w_;
        leftup.y = center.y - h_;
        leftup.h = h_;
        leftup.w = w_;

        rightup.x = center.x + w_;
        rightup.y = center.y - h_;
        rightup.h = h_;
        rightup.w = w_;

        leftdown.x = center.x - w_;
        leftdown.y = center.y + h_;
        leftdown.h = h_;
        leftdown.w = w_;

        rightdown.x = center.x + w_;
        rightdown.y = center.y + h_;
        rightdown.h = w_;
        rightdown.w = h_;

        cen_r = 231; cen_g = 228; cen_b = 20;
        edg_r = 255; edg_g = 114; edg_b = 20;
        cor_r = 255; cor_g = 0;   cor_b = 20; 

        center_color = {Uint8(cen_r), Uint8(cen_g), Uint8(cen_b), 0};
        edge_color = {Uint8(edg_r), Uint8(edg_g), Uint8(edg_b), 0};
        corner_color = {Uint8(cor_r), Uint8(cor_g), Uint8(cor_b), 0};       

        disperse_count = 0;
    }

    void explode(int x, int y);
    void disperse();
    void fall();
    void draw();

    bool alive() const { return alive_; }
    void alive(bool alive) { alive_ = alive; }
    
    Rect Leftup() const { return leftup; }
    Rect Up() const { return up; }
    Rect Rightup() const { return rightup; }
    Rect Left() const { return left; }
    Rect Center() const { return center; }
    Rect Right() const { return right; }
    Rect Leftdown() const { return leftdown; }
    Rect Down() const { return down; }
    Rect Rightdown() { return rightdown; }
    
private:
    int x_, y_, w_, h_;

    int cen_r, cen_g, cen_b;
    int edg_r, edg_g, edg_b;
    int cor_r, cor_g, cor_b;
    
    Color center_color;
    Color edge_color;
    Color corner_color;
        
    Surface & surface_;
    
    Rect leftup, up, rightup;
    Rect left, center, right;
    Rect leftdown, down, rightdown;
    
    bool alive_;

    int disperse_count;

    static Sound sound;
};

#endif

void build_explosion(Surface &, std::vector < Explosion > &);
void find_explosion(std::vector < Explosion > &, int, int);
