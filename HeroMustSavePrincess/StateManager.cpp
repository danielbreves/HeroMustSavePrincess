//
//  StateManager.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "StateManager.h"
#include "GameState.h"

StateManager::StateManager(sf::RenderWindow* rw, GameState* start) {
    window = rw;
    running = true;
    prev = NULL;
    current = start;
    current->Init(this);
}

StateManager::~StateManager() {
    delete prev;
    delete current;
}

void StateManager::ChangeState(GameState* toState) {
	if (toState != prev) {
        delete prev;
	}
    
    current = toState;
    current->Init(this);
}

void StateManager::HandleEvents() {
    current->HandleEvents(this);
}

void StateManager::Update() {
    current->Update(this);
}

void StateManager::Render() {
    window->clear();
    current->Render(this);
    window->display();
}

bool StateManager::Running() {
    return running;
}

void StateManager::Quit() {
    running = false;
}