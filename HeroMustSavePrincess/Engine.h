//
//  Engine.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Engine__
#define __HeroMustSavePrincess__Engine__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.h"
#include "ImageManager.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "Level.h"
#include "Tile.h"
#include "Player.h"

class Engine : public GameState {
    Player *player;
    Camera camera;
    std::vector<Level> levels;
    int current = 0;
    
public:
	Engine();
    Engine(int width, int height);
	~Engine();
    
	void Init(StateManager* manager);
    void CreateLevels();
    void HandleEvents(StateManager* manager);
	void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__HeroMustSavePrincess__Engine__) */
