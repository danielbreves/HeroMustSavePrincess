//
//  StateManager.h
//  Spike6
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __Spike6__StateManager__
#define __Spike6__StateManager__

#include <iostream>
#include <SFML/Graphics.hpp>

class GameState;

class StateManager {
    bool running;
    GameState* state;
    sf::RenderWindow* window;
    
public:
    StateManager(sf::RenderWindow* rw);
    ~StateManager();
    
    void Init(GameState* start);
    void ChangeState(GameState* state);
    sf::RenderWindow* GetWindow() {return window;}
    void HandleEvents();
    void Update();
    void Render();
    bool Running();
    void Quit();
};

#endif /* defined(__Spike6__StateManager__) */
