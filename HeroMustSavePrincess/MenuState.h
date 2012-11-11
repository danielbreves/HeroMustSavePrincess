//
//  MenuState.h
//  Spike6
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __Spike6__MenuState__
#define __Spike6__MenuState__

#include <iostream>
#include <vector>
#include "GameState.h"

class MenuState : public GameState {
//    enum MenuOption {
//        PLAY,
//        ABOUT,
//        EXIT,
//        FIRST = PLAY,
//        LAST = EXIT
//    };
    std::vector<std::string> menuOptions;
    int selected;
    
public:
    MenuState();
    ~MenuState();
    
    void Init(StateManager* manager);
    
    void HandleEvents(StateManager* manager);
    void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__Spike6__MenuState__) */
