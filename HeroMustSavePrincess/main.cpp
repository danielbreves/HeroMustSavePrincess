//
//  main.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 7/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "GameState.h"
#include "MenuState.h"

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480
#define SCREEN_BPP      32
#define FPS             25

int main (int argc, const char * argv[])
{
//	Engine* engine = new Engine(800, 600);
//    
//	try {
//		engine->Go();
//	} catch (char* e) {
//        printf("%s", e);
//        return EXIT_FAILURE;
//	}
//    
//    delete engine;
    
    sf::Clock clock;
    
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP), "Hero Must Save Princess", sf::Style::Titlebar | sf::Style::Close);
    
    if(!window)
		return EXIT_FAILURE;
    
    StateManager manager(window);
    GameState *start = new MenuState();
    
    manager.Init(start);
    
    sf::Int32 timelastcall = clock.getElapsedTime().asMilliseconds();
    
	//Loop until our window is closed
	while(window->isOpen() && manager.Running()) {
        if (clock.getElapsedTime().asMilliseconds() - timelastcall > 1000/FPS) {
            manager.HandleEvents();
            manager.Update();
            timelastcall = clock.getElapsedTime().asMilliseconds();
        }
        manager.Render();
	}
    
    delete window;

    return EXIT_SUCCESS;
}
