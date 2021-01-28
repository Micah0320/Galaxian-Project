
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
#include "stars.h"
//#include "fleet.h"

void play(Surface & surface, Event & event);
void DetectCollision(Player &, std::vector<RedAlien> &, Surface &, bool &);
void DetectCollision(Player &, std::vector<PurpleAlien> &, Surface &, bool &);
void DetectCollision(Player &, std::vector<BlueAlien> &, Surface &, bool &);
void DetectCollision(Player &, std::vector<FlagAlien> &, Surface &, bool &);
int main_menu(Surface & surface, Event & event)
{
    Galaxy galaxy(surface);
    galaxy.build();
    Font font("fonts/FreeSerifBold.ttf", 50);
    Font font_options("fonts/FreeSerifBold.ttf", 30);
    Font score("fonts/FreeSerifBold.ttf", 20);
    Image Title(font.render("STARLAXIAN", YELLOW));
    Rect title_rect = Title.getRect();
    title_rect.x = 175;
    title_rect.h = H / 2;

    Image play_(font_options.render("  Micah Arndt", YELLOW));
    Image exit_(font_options.render("  Press Space to Play", YELLOW));
    
    Rect rect_play = play_.getRect();
    rect_play.x = (title_rect.x + 50);
    rect_play.y = title_rect.y + 75;
    Rect rect_exit = exit_.getRect();
    rect_exit.y = rect_play.y + 300;
    rect_exit.x = rect_play.x - 50;
    
    Image pointF(score.render("  250", RED));
    Image pointR(score.render("  100", RED));
    Image pointP(score.render("  50", RED));
    Image pointB(score.render("  25", RED));
    Rect pointF_rect = pointF.getRect();
    pointF_rect.y = rect_play.y + 75;
    pointF_rect.x = rect_play.x + 75;
    Rect pointR_rect = pointR.getRect();
    pointR_rect.y = pointF_rect.y + 50;
    pointR_rect.x = rect_play.x + 75;
    Rect pointP_rect = pointP.getRect();
    pointP_rect.y = pointR_rect.y + 50;
    pointP_rect.x = rect_play.x + 75;
    Rect pointB_rect = pointB.getRect();
    pointB_rect.y = pointP_rect.y + 50;
    pointB_rect.x = rect_play.x + 75;
    
    bool F_in_place = 0;
    bool R_in_place = 0;
    bool P_in_place = 0;
    bool B_in_place = 0;
    
    
    Image Flag("images/galaxian/GalaxianFlagship.gif");
    Image Red("images/galaxian/GalaxianRedAlien.gif");
    Image Blue("images/galaxian/GalaxianAquaAlien.gif");
    Image Purple("images/galaxian/GalaxianPurpleAlien.gif");
    Rect FlagRect = Flag.getRect();
    FlagRect.y = pointF_rect.y;
    FlagRect.x = W;
    Rect RedRect = Red.getRect();
    RedRect.y = pointR_rect.y;
    RedRect.x = W;
    Rect BlueRect = Blue.getRect();
    BlueRect.y = pointB_rect.y;
    BlueRect.x = W;
    Rect PurpleRect = Purple.getRect();
    PurpleRect.y = pointP_rect.y;
    PurpleRect.x = W;
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        KeyPressed key = get_keypressed();
        if (key[SPACE])
        {
            return 1;
        }
        if (key[UPARROW])
        {
            return 2;
            
        }

         if (key[DOWNARROW])
        {
            
            return 3;
            
        }
        surface.lock();
        surface.fill(BLACK);
        surface.put_image(Title, title_rect);
        if(!F_in_place)
        {
            FlagRect.x -= 5;
            if (FlagRect.x == title_rect.x)
            {
                F_in_place = 1;
            }
        }

        if(F_in_place)
        {
            surface.put_image(pointF, pointF_rect);
            if(!R_in_place)
                RedRect.x -= 5;
            if (RedRect.x == title_rect.x)
            {
                R_in_place = 1;
            }
        }
        if(R_in_place)
        {
            surface.put_image(pointR, pointR_rect);
            if (!P_in_place)
                PurpleRect.x -= 5;
            if (PurpleRect.x == title_rect.x)
            {
                P_in_place = 1;
            }
        }
        if(P_in_place)
        {
            surface.put_image(pointP, pointP_rect);
            if(!B_in_place)
                BlueRect.x -= 5;
            if (BlueRect.x == title_rect.x)
            {
                B_in_place = 1;
            }
        }

        if (B_in_place)
        {
             surface.put_image(pointB, pointB_rect);
        }
        galaxy.draw();
        surface.put_image(Flag, FlagRect);
        surface.put_image(Red, RedRect);
        surface.put_image(Purple, PurpleRect);
        surface.put_image(Blue, BlueRect);
        surface.put_image(play_, rect_play);
        surface.put_image(exit_, rect_exit);
        surface.unlock();
        surface.flip();
        delay(20);
    }
    return 3;
}


int main(int argc, char **argv)
{
    
    srand((unsigned int) time(NULL));

    Surface surface(W, H);
    Event event;
   
    while (1)
    {
        if (event.poll() && event.type() == QUIT)
            break;
        int option = main_menu(surface, event);
        switch (option)
        {
            case 0:
                option = main_menu(surface, event);
                break;
                
            case 1:
                play(surface, event);
                break;
           
            case 3:
                break;
        }
        if (option == 3)
        {
            break;
        }
    }
    
    return 0;
}

    
void play(Surface & surface, Event & event)
{
    int endLoop = 0;
    Player player(surface);
    const int PLAYER_R = 227;
    const int PLAYER_G = 42;
    const int PLAYER_B = 5;
    Laser laser(surface, PLAYER_R, PLAYER_G, PLAYER_B);
    std::vector<Laser>playerLaser;
    for (int i = 0; i < 5; ++i)
    {
        Laser pL(surface, PLAYER_R, PLAYER_G, PLAYER_B);
        playerLaser.push_back(pL);
    }
    const int ENEMY_R = 3;
    const int ENEMY_G = 243;
    const int ENEMY_B = 21;
    
    std::vector<Laser>enemyLasers;
    for (int i = 0; i < 1000; ++i)
    {
        Laser eL(surface, ENEMY_R, ENEMY_G, ENEMY_B, 0);
        enemyLasers.push_back(eL);
    }
    Sound sound("sounds/laser.wav");
    Music music("sounds/GameMusic.ogg");
    
    //Elements to creating the HUD
    char str_score[20];
    char str_wave[3];
    char lives_remaining[1];
    Font font("fonts/FreeSerifBold.ttf", 20);
    Font WaveFont("fonts/FreeSansOblique.ttf", 15);
    
    Image ScoreLable(font.render("SCORE: ", WHITE));
    Rect score_lable_rect = ScoreLable.getRect();
    Image WaveLable(WaveFont.render("WAVE: ", YELLOW));
    Rect wave_lable_rect = WaveLable.getRect();
    wave_lable_rect.y = H - 30;
    wave_lable_rect.x = 0;

    Image GameOver(font.render("GAME OVER", RED));
    Rect gameOver_rect = GameOver.getRect();
    gameOver_rect.x = (W / 2) - 75;
    gameOver_rect.y = (H / 2);
    bool gameOver = 0;
    score_lable_rect.x = W / 2 - 100;

    Image you_Lives("images/sw/swXWing.gif");
    Rect you_Lives_rect = you_Lives.getRect();
    you_Lives_rect.x = W - (you_Lives_rect.w + 50);
    you_Lives_rect.y = H - (you_Lives_rect.h);
    Image x(WaveFont.render("x", YELLOW));
    Rect x_rect = ScoreLable.getRect();
    
    //Creates Various Vectors
    std::vector<RedAlien> rAliens;
    std::vector<BlueAlien>bAliens;
    std::vector<PurpleAlien>pAliens;
    std::vector<FlagAlien>fAliens;
    int Level = 1;

    //Creates Background
    Galaxy galaxy(surface);
    galaxy.build();
    //Creates a Fleet rectangle//
    Rect Fleet;
    Fleet.x = 0;
    Fleet.y = 0;
    Fleet.h = 0;
    Fleet.w = 0;
    double fleetSpeed = 3.1;
    
    //Creates the First row of the Fleet (The Red and Yellow Aliens
    for (int i = 0; i < 2; ++i)
    {
        FlagAlien f(surface, i);
        fAliens.push_back(f);
    }
    for (int i = 0; i < 10; ++i)
    {
        RedAlien r(surface,  i);
        Fleet.w +=r.w() + 2;
        if(i == 0)
        {
            Fleet.y = r.y();
            Fleet.h = 5 * r.h();
            Fleet.x = r.x();
        }
        rAliens.push_back(r);
    }
    rAliens.shrink_to_fit();
    //Creates the Second Row of the fleet
    for(int i = 0; i < 10; ++i)
    {
        BlueAlien b(surface, i);
        bAliens.push_back(b);
    }
    bAliens.shrink_to_fit();
    //Creates the third Row of the Fleet
    for(int i = 0; i < 10; ++i)
    {
        
        PurpleAlien p(surface, i);
        pAliens.push_back(p);
    }
    pAliens.shrink_to_fit();
    int numberAliens = rAliens[0].numberAlive();
    bool canAttack = 0;
    bool immune = 0;
    //Declares various Timers
    int ticks = getTicks();
    int newTicks = ticks + 500;
    int endTicks = 0;
    int stopT = 0;
    int immunityTick = 0;
    int stopImmunity = 0;
    
    music.play();
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        //Gets the total number of Aliens
        numberAliens = rAliens[0].numberAlive();
        
        //Displayes the Score
        sprintf(str_score, "%d", player.score());
        Image score(font.render(str_score, WHITE));
        Rect score_rect = score.getRect();
        score_rect.x = score_lable_rect.x + 150;
        
        //Displays the Current Wave
        sprintf(str_wave, "%d", Level);
        Image wave(WaveFont.render(str_wave, YELLOW));
        Rect wave_rect = wave_lable_rect;
        wave_rect.x = wave_lable_rect.x + 75;
        
        //Displays Your Total number of Lives.
        
        sprintf(lives_remaining, "%d", player.lives() - 1);
        Image LivesNumber(WaveFont.render(lives_remaining, YELLOW));
        Rect LivesNumber_r = LivesNumber.getRect();
        LivesNumber_r.x = you_Lives_rect.x + 20 + you_Lives_rect.w;
        LivesNumber_r.y = you_Lives_rect.y;
        x_rect.x = LivesNumber_r.x + you_Lives_rect.w + 10;
        x_rect.y = LivesNumber_r.y;

        //Determines if an alien can attack
        if (rand() % 150 == 117 || rand() % 150 == 42 && player.isAlive() && !gameOver && !immune)
        {
            canAttack = 1;
            int row = rand() % 4;
            int col = rand() % 10;
            sound.play();

            switch (row)
            {
                case 0:
                    if(!bAliens[col].getDive())
                        bAliens[col].attack(enemyLasers);
                    
                    break;
                case 1:
                    if(!pAliens[col].getDive())
                        pAliens[col].attack(enemyLasers);
                    
                    break;
                case 2:
                    if(!rAliens[col].getDive())
                    rAliens[col].attack(enemyLasers);
                   
                    break;
                case 3:
                    col = rand() % 2;
                    if (!col)
                    {
                        if (!fAliens[col].getDive())
                        {
                            fAliens[col].attack(enemyLasers);
                            rAliens[1].attack(enemyLasers);
                            rAliens[2].attack(enemyLasers);
                            rAliens[3].attack(enemyLasers);
                        }
                    }

                    else
                    {
                        if(!fAliens[col].getDive())
                        {
                            fAliens[col].attack(enemyLasers);
                            rAliens[6].attack(enemyLasers);
                            rAliens[7].attack(enemyLasers);
                            rAliens[8].attack(enemyLasers);
                        }
                    }
            }
        }
        
        KeyPressed key = get_keypressed();
        
       
        
        
        //KeyPressed keypressed = get_keypressed();
        
        player.move();
        for (int i = 0; i < 5; ++i)
        {
            if (playerLaser[i].y() < 0)
            {
                playerLaser[i].stopFire();
            }
        }
        
        surface.lock();
        surface.fill(BLACK);
        
        //The Following Logic determines if a laser can fire and moves/draws it
        if (key[SPACE] && player.isAlive())
        {
            ticks = getTicks();
            //std::cout << ticks << std::endl;
            if (ticks >= newTicks)
            {
                newTicks = ticks + 500;
                int available = -1;
                for (int i = 0; i < 5; ++i)
                {
                    
                    if (!playerLaser[i].isAlive())
                    {
                        available = i;
                        break;
                    }
                    
               
                }
            
                if (available >= 0)
                {
                    sound.play();
                    playerLaser[available].fire(player.x() + (player.w() / 2), player.y() + 10);
                }
            }
        }
        for (int i = 0; i < 5; ++i)
        {
            if (playerLaser[i].isAlive())
            {
                playerLaser[i].move();
            
                playerLaser[i].draw();
            }
        }
        
        
        //moves the enemy
        
        //The following logic moves the Alien fleet
        //and detects collisions with the bounds of the game
        Fleet.x += fleetSpeed;
        if (Fleet.x + Fleet.w > W)
        {
            
            for (int i = 0; i < 10; ++i)
            {
                if (i < 2)
                    fAliens[i].speedUpdate();
                rAliens[i].speedUpdate();
                bAliens[i].speedUpdate();
                pAliens[i].speedUpdate();
                
            }
            fleetSpeed *= -1;
        }
        if (Fleet.x < 0)
        {
            rAliens[0].x() = 0;
            bAliens[0].x() = 0;
            pAliens[0].x() = 0;
            for (int i = 0; i < 10; ++i)
            {
                if (i < 2)
                {
                    fAliens[i].speedUpdate();
                    if(!fAliens[i].getDive())
                        fAliens[i].StartPos();
                }
                rAliens[i].speedUpdate();
                bAliens[i].speedUpdate();
                pAliens[i].speedUpdate();
                if (i != 0)
                {
                    rAliens[i].x() = 0 + rAliens[i].w() * i;
                    bAliens[i].x() = 0 + bAliens[i].w() * i;
                    pAliens[i].x() = 0 + pAliens[i].w() * i;
                }
            }
            fleetSpeed *= -1;
        }
        //Moves the Alien Fleet
        for (int i = 0; i < 10; ++i)
        {
            if (i < 2)
                fAliens[i].move();
            rAliens[i].move();
            bAliens[i].move();
            pAliens[i].move();
            
        }

        //moves enemy lasers
        for (int i = 0; i < 5; ++i)
        {
            if (enemyLasers[i].isAlive() && !immune)
            {
                enemyLasers[i].move();
                player.DetectCollision(enemyLasers[i]);
                enemyLasers[i].draw();
            }
        }
        //Collision Detection between laser and fleet
        for (int i = 0; i < 5; ++i)
        {
            if (playerLaser[i].isAlive())
            {
               
                for(int k = 0; k < 10; ++k)
                {
                    bAliens[k].DetectCollision(playerLaser[i], player.score());
                }
                for(int k = 0; k < 10; ++k)
                {
                    pAliens[k].DetectCollision(playerLaser[i], player.score());
                }
                for(int k = 0; k < 10; ++k)
                {
                    rAliens[k].DetectCollision(playerLaser[i], player.score());
                }
               
                for (int k = 0; k < 2; ++k)
                {
                    fAliens[k].DetectCollision(playerLaser[i], player.score());
                }
                
            }
        }
        //Detects collisions between player and Aliens
        if (!immune)
            DetectCollision(player, rAliens, surface, immune);
        if (!immune)
            DetectCollision(player, bAliens, surface, immune);
        if (!immune)
            DetectCollision(player, pAliens, surface, immune);
        if (!immune)
            DetectCollision(player, fAliens, surface, immune);
        //Draws The HUD
        surface.put_image(score, score_rect);
        surface.put_image(ScoreLable, score_lable_rect);
        surface.put_image(wave, wave_rect);
        surface.put_image(WaveLable, wave_lable_rect);
        surface.put_image(you_Lives, you_Lives_rect);
        surface.put_image(x, x_rect);
        surface.put_image(LivesNumber, LivesNumber_r);
        
        
        //Draws the Aliens
        for (int i = 0; i < 10; ++i)
        {
            if (i < 2)
            {
                fAliens[i].Draw();
            }
            rAliens[i].Draw();
            bAliens[i].Draw();
            pAliens[i].Draw();
        }
        player.Draw();
        if (player.lives() == 0 && !gameOver)
        {
            gameOver = 1;
            surface.put_image(GameOver, gameOver_rect);
            stopT = getTicks() + 5000;       
        }
        if (gameOver)
        {
            surface.put_image(GameOver, gameOver_rect);
        }

        galaxy.draw();
        surface.unlock();
        surface.flip();
        if (gameOver)
        {
            endTicks = getTicks();
            
                KeyPressed end = get_keypressed();
                if (end[UPARROW])
                    break;
                if (endTicks >= stopT)
                    break;
        }
        if (numberAliens == 0)
        {
            for(int i = 0; i < 10; ++i)
            {
                if (i < 2)
                {
                    fAliens[i].reset();
                }
                rAliens[i].reset(i);
                bAliens[i].reset(i);
                pAliens[i].reset(i);
            }
            Fleet.x = rAliens[0].x();
            ++Level;
        }
        for (int i = 0; i < 5; ++i)
        {
            if (enemyLasers[i].y() > H)
            {
                enemyLasers[i].isAlive() = 0;
            }
        }
        canAttack = 0;
        if (!player.isAlive() && player.lives() > 0)
        {
            immunityTick = getTicks();
            stopImmunity = getTicks() + 3500;
            immune = 1;
            player.revive();
        }
        if (immune)
        {
            immunityTick = getTicks();
            if (immunityTick >= stopImmunity)
            {
                immune = 0;
            }
        }
        
       
        
        delay(20);
    }
}

//Aliens are renamed Laser in order to make it easier to copy/paste code
void DetectCollision(Player & player, std::vector<RedAlien> & laser,
                     Surface & surface, bool & immune)
{
    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 10; ++i)
    {
        if (laser[i].getDive() && laser[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = laser[i].x() + laser[i].w();
            double corner2y = laser[i].y() + laser[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < laser[i].x() && laser[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) &&player.isAlive())
            {
               
                laser[i].die();
                player.die();
                //std::cout << numAlive <<std::endl;;
                player.score() += laser[i].pointValue();
                //explode.play();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((laser[i].x() < player.x() && player.x() < corner2x) &&
                (player.y() < laser[i].y() && laser[i].y() < corner1y) &&player.isAlive())
            {
                laser[i].die();
                player.die();
                player.score() += laser[i].pointValue();
                //explode.play();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                
                immune = 1;
                break;
            }
        }
        return;
    }
}

void DetectCollision(Player & player, std::vector<PurpleAlien> &laser,
                     Surface & surface, bool & immune)
{
    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 10; ++i)
    {
        if (laser[i].getDive() && laser[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = laser[i].x() + laser[i].w();
            double corner2y = laser[i].y() + laser[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < laser[i].x() && laser[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) && player.isAlive())
            {
               
                laser[i].die();
                player.die();
                //std::cout << numAlive <<std::endl;;
                player.score() += laser[i].pointValue();
                //explode.play();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((laser[i].x() < player.x() && player.x() < corner2x)
                && (player.y() < laser[i].y() && laser[i].y() < corner1y) &&player.isAlive())
            {
                laser[i].die();
                player.die();
                player.score() += laser[i].pointValue();
                //explode.play();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
        }
    }
}
void DetectCollision(Player & player, std::vector<BlueAlien> &laser,
                     Surface & surface, bool & immune)
{
    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 10; ++i)
    {
        if (laser[i].getDive() && laser[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = laser[i].x() + laser[i].w();
            double corner2y = laser[i].y() + laser[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < laser[i].x() && laser[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) &&player.isAlive())
            {
               
                laser[i].die();
                player.die();
                //std::cout << numAlive <<std::endl;;
                player.score() += laser[i].pointValue();
                //explode.play();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((laser[i].x() < player.x() && player.x() < corner2x) &&
                (player.y() < laser[i].y() && laser[i].y() < corner1y) &&player.isAlive())
            {
                laser[i].die();
                player.die();
                player.score() += laser[i].pointValue();
                //explode.play();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
        }
    }
}
void DetectCollision(Player & player, std::vector<FlagAlien> &laser,
                     Surface & surface, bool & immune)
{
    Sound explode("sounds/explosion.wav");
    for (int i = 0; i < 2; ++i)
    {
        if (laser[i].getDive() &&laser[i].Alive())
        {
            double corner1x = player.x() + player.w();
            double corner1y = player.y() + player.h();
            
            double corner2x = laser[i].x() + laser[i].w();
            double corner2y = laser[i].y() + laser[i].h();
            
            int center_x = player.x() + (player.w() / 2);
            int center_y = player.y() + (player.h() / 2);
            int r = 2;
            
            if ((player.x() < laser[i].x() && laser[i].x() < corner1x) &&
                (player.y() < corner2y && corner2y < corner1y) &&player.isAlive())
            {
               
                laser[i].die();
                player.die();
                //std::cout << numAlive <<std::endl;;
                player.score() += laser[i].pointValue();
                //explode.play();
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
            if ((laser[i].x() < player.x() && player.x() < corner2x) && (player.y() < laser[i].y() && laser[i].y() < corner1y) &&player.isAlive())
            {
                laser[i].die();
                player.die();
                player.score() += laser[i].pointValue();
                //explode.play();
                int r = 2;
                for (int i = 0; i < 75; ++i)
                {
                    surface.put_circle(center_x, center_y, r, 254, 4, 4);
                    surface.put_circle(center_x, center_y, r / 2, 232, 215, 8);
                    if (i % 2 == 0)
                        ++r;
                }
                immune = 1;
                break;
            }
        }
    }
}
