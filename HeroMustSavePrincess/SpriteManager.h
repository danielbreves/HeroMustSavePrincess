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
//#include "Sprite.h"
#include "Camera.h"
//#include "Level.h"
using namespace std;

class Level;
class Sprite;

class SpriteManager {
    vector<Sprite*> sprites;
    
public:
    SpriteManager();
    ~SpriteManager();
    
    const vector<Sprite*>* GetSprites() const;
    void AddSprite(Sprite* sprite);
    void Update(Camera* camera, Level* level);
    void Draw(sf::RenderWindow* rw, Camera* camera);
};

#endif /* defined(__HeroMustSavePrincess__SpriteManager__) */
