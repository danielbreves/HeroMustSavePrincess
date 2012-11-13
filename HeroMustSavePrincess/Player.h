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
#include <SFML/Audio.hpp>
#include "SpriteManager.h"
#include "Sprite.h"

class Player : public Sprite {
    sf::Texture heart;
    int speed;
    sf::SoundBuffer no;
    sf::SoundBuffer hit;
    sf::SoundBuffer kiss;
    sf::Sound sound;
    
public:
    Player() {};
    Player(sf::Texture &img, int w, int h, int speed);
    ~Player();
    void CreateAnimations(int rows);
    void Move(Level* level, int x, int y);
    void HandleCollision(Sprite* sprite, Level* level);
    void Update(const vector<Sprite*>* sprites, Level* level);
    void Draw(sf::RenderWindow* rw, Camera* camera);
};

#endif /* defined(__HeroMustSavePrincess__Player__) */
