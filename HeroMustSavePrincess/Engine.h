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
#include "Camera.h"
#include "Level.h"
#include "Tile.h"

class Engine
{
private:
	sf::RenderWindow* window;    
    ImageManager imageManager;
    sf::Vector2i videoSize;
    int tileSize;
    Camera* camera;
    Level* currentLevel;
    bool mouseDown;
    
	bool Init();
	void MainLoop();
	void RenderFrame();
	void ProcessInput();
	void Update();
    void LoadImages();
    void LoadLevel();
    
public:
	Engine(int w, int h, int tSize);
	~Engine();
    
	void Go();					//Starts the engine
};

#endif /* defined(__HeroMustSavePrincess__Engine__) */
