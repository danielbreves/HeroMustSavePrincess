//
//  Animation.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Animation__
#define __HeroMustSavePrincess__Animation__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

typedef struct {
    sf::IntRect image;
    sf::Uint32 duration;
} Frame;

class Animation {
    sf::RenderWindow* screen;
    vector<Frame> frames;
    int currFrame;
    sf::Clock clock;
    sf::Time ticks;
    
public:
    Animation();
    void Reset();
    void AddFrame(sf::IntRect image, sf::Uint32 duration);
    void Update();
    void Draw(sf::RenderWindow* rw, const sf::Texture* texture, const sf::Vector2i position);
};

#endif /* defined(__HeroMustSavePrincess__Animation__) */
