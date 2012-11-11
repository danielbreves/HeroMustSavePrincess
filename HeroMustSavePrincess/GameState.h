//
//  GameState.h
//  Spike6
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __Spike6__GameState__
#define __Spike6__GameState__

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateManager.h"

class GameState {

public:    
    GameState() {}
    virtual ~GameState() {};
    
    virtual void Init(StateManager* manager) = 0;
    
    virtual void HandleEvents(StateManager* manager) = 0;
    virtual void Update(StateManager* manager) = 0;
    virtual void Render(StateManager* manager) = 0;
};

#endif /* defined(__Spike6__GameState__) */
