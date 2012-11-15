//
//  GameState.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__GameState__
#define __HeroMustSavePrincess__GameState__

#include <SFML/Graphics.hpp>
#include <iostream>

class StateManager;

class GameState {
    
public:
    GameState() {}
    virtual ~GameState() {}
    
    virtual void Init(StateManager* manager) = 0;

    virtual void HandleEvents(StateManager* manager) = 0;
    virtual void Update(StateManager* manager) = 0;
    virtual void Render(StateManager* manager) = 0;
};

#endif /* defined(__HeroMustSavePrincess__GameState__) */
