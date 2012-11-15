//
//  MessageState.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__MessageState__
#define __HeroMustSavePrincess__MessageState__

#include <iostream>
#include "GameState.h"

class MessageState : public GameState {
    GameState* nextState;
    sf::Font bebasneue;
    sf::Text title;
    std::string message;
    int frames;
    
public:
    MessageState() {};
    MessageState(std::string msg, int f, GameState* next);
    ~MessageState() {}
    
    void Init(StateManager* manager);
    
    void CreateLayout(sf::Vector2u windowSize);
    void HandleEvents(StateManager* manager);
    void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__HeroMustSavePrincess__MessageState__) */
