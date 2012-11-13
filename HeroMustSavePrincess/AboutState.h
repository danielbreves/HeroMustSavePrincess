//
//  AboutState.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__AboutState__
#define __HeroMustSavePrincess__AboutState__

#include <iostream>
#include "GameState.h"

class AboutState : public GameState {
    
public:
    AboutState();
    ~AboutState();
    
    void Init(StateManager* manager);
    
    void HandleEvents(StateManager* manager);
    void Update(StateManager* manager);
    void Render(StateManager* manager);
};

#endif /* defined(__HeroMustSavePrincess__AboutState__) */
