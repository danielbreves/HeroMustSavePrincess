//
//  Princess.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Princess__
#define __HeroMustSavePrincess__Princess__

#include <iostream>
#include "SpriteManager.h"
#include "Sprite.h"

class Princess : public Sprite {
    
public:
    Princess(sf::Texture &img, sf::Vector2i p, int w, int h);
    ~Princess();
    void CreateAnimations(int rows);
    void HandleCollision(Sprite* sprite, Level* level);
    void Update(Camera* camera, Level* level);
    void Draw(sf::RenderWindow* rw, Camera* camera);
};

#endif /* defined(__HeroMustSavePrincess__Princess__) */
