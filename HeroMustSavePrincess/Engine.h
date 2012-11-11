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
#include "ImageManager.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "Level.h"
#include "Tile.h"
#include "Player.h"

class Engine
{
private:
	sf::RenderWindow* window;    
    ImageManager imageManager;
    sf::Vector2i videoSize;
    int tileSize;
    SpriteManager* spriteManager;
    Player* player;
    Camera* camera;
    Level* currentLevel;
    bool mouseDown;
    sf::Clock clock;
    
	bool Init();
	void MainLoop();
	void RenderFrame();
	void ProcessInput();
	void Update();
    
public:
	Engine(int w, int h);
	~Engine();
    //bool CheckCollision(sf::IntRect A, sf::IntRect B);
    
	void Go();					//Starts the engine
};

#endif /* defined(__HeroMustSavePrincess__Engine__) */
