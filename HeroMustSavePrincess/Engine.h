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
#include "GameState.h"
#include "ImageManager.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "Level.h"
#include "Tile.h"
#include "Player.h"

class Engine : public GameState {
	//sf::RenderWindow* window;
    ImageManager imageManager;
    sf::Vector2i videoSize;
    SpriteManager* spriteManager;
    Player* player;
    Camera* camera;
    Level* currentLevel;
    sf::Clock clock;
    
public:
	Engine();
	~Engine();
    
    //void Run();					//Starts the engine
	void Init(StateManager* manager);
	//void MainLoop();
    void HandleEvents(StateManager* manager);
	void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__HeroMustSavePrincess__Engine__) */
