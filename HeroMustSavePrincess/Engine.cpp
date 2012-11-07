//
//  Engine.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Engine.h"


Engine::Engine()
{
    
}

Engine::~Engine()
{
    
}

bool Engine::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "RPG");
    
	if(!window)
		return false;
    
	return true;
}

void Engine::RenderFrame()
{
    
}

void Engine::ProcessInput()
{
	sf::Event evt;
	//Loop through all window events
	while(window->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed)
			window->close();
	}
}

void Engine::Update()
{
    
}

void Engine::MainLoop()
{
	//Loop until our window is closed
	while(window->isOpen())
	{
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Engine::Go()
{
	if(!Init())
		throw "Could not initialize Engine";
    
	MainLoop();
}
