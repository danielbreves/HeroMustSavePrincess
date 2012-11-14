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
#include "Player.h"
#include "Animation.h"
#include "Camera.h"
using namespace std;

class Level;
class Sprite;

class SpriteManager {
    vector<Sprite*> sprites;
    
public:
    SpriteManager();
    ~SpriteManager();
    
    const vector<Sprite*>* GetSprites() const;
    void CheckCollisions(Player* player, Level* level);
    bool CheckCollision(Sprite* A, Sprite* B);
    void AddSprite(Sprite* sprite);
    void Update(Camera* camera, Level* level);
    void Draw(sf::RenderWindow* rw, Camera* camera);
};

#endif /* defined(__HeroMustSavePrincess__SpriteManager__) */
