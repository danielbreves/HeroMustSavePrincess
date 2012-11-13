//
//  GameMessageState.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__GameMessageState__
#define __HeroMustSavePrincess__GameMessageState__

#include <iostream>
#include "GameState.h"

class GameMessageState : public GameState {
    GameState* nextState;
    std::string message;
    int frames;
    
public:
    GameMessageState();
    GameMessageState(std::string msg, int f, GameState* next);
    ~GameMessageState();
    
    void Init(StateManager* manager);
    
    void HandleEvents(StateManager* manager);
    void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__HeroMustSavePrincess__GameMessageState__) */
