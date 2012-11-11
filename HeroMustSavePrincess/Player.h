//
//  Player.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 8/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Player__
#define __HeroMustSavePrincess__Player__

#include <iostream>
#include "SpriteManager.h"
#include "Sprite.h"

class Player : public Sprite {
    int speed;
    int life = 5;
    
public:
    Player(sf::Texture &img, sf::Vector2i p, int w, int h, int speed);
    ~Player();
    void Move(Level* level, int x, int y);
    void CheckCollisions(vector<Sprite*>* sprites, Level* level);
    void Update(Level* level);
};

#endif /* defined(__HeroMustSavePrincess__Player__) */
