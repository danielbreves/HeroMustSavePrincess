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

class Engine
{
private:
	//SFML Render Window
	sf::RenderWindow* window;
    
	//Initializes the engine
	bool Init();
	//Main Game Loop
	void MainLoop();
	//Renders one frame
	void RenderFrame();
	//Processes user input
	void ProcessInput();
	//Updates all Engine internals
	void Update();
    
public:
	Engine();
	~Engine();
    
	void Go();					//Starts the engine
};

#endif /* defined(__HeroMustSavePrincess__Engine__) */
