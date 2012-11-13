//
//  StateManager.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__StateManager__
#define __HeroMustSavePrincess__StateManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameState.h"

class StateManager {
    bool running;
    GameState* prev;
    GameState* current;
    sf::RenderWindow* window;
    
public:
    StateManager(sf::RenderWindow* rw, GameState* start);
    ~StateManager();
    
    void ChangeState(GameState* state);
    sf::RenderWindow* GetWindow() {return window;}
    void HandleEvents();
    void Update();
    void Render();
    bool Running();
    void Quit();
};

#endif /* defined(__HeroMustSavePrincess__StateManager__) */
