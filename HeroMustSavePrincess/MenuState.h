//
//  MenuState.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__MenuState__
#define __HeroMustSavePrincess__MenuState__

#include <iostream>
#include <vector>
#include "GameState.h"

class MenuState : public GameState {
    sf::Font silkworm, bebasneue;
    sf::Text title;
    std::vector<sf::Text> menuOptions;
    int selected;
    
public:
    MenuState() {};
    ~MenuState() {};
    
    void Init(StateManager* manager);
    
    void CreateLayout(sf::Vector2u windowSize);
    void HandleEvents(StateManager* manager);
    void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__HeroMustSavePrincess__MenuState__) */
