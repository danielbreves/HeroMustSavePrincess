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
#include <queue>
#include "GameState.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"

class Engine : public GameState {
    Player *player;
    Camera camera;
    std::queue<Level> levels;
    int currLevel = 1;
    
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
