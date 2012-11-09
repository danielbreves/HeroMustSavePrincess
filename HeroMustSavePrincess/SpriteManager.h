//
//  SpriteManager.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__SpriteManager__
#define __HeroMustSavePrincess__SpriteManager__

#include <iostream>
#include <vector>
#include "Animation.h"
#include "Sprite.h"
#include "Camera.h"
#include "Level.h"
using namespace std;

class SpriteManager {
    vector<Sprite*> sprites;

    
public:
    SpriteManager(Level* level, int tileSize);
    ~SpriteManager();
    vector<Sprite*>* GetSprites();
    void Update(Camera* camera, int tileSize);
    void Draw(sf::RenderWindow* rw, Camera* camera);
};

#endif /* defined(__HeroMustSavePrincess__SpriteManager__) */
