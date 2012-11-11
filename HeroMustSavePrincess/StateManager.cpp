//
//  StateManager.cpp
//  Spike6
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "StateManager.h"
#include "GameState.h"

StateManager::StateManager(sf::RenderWindow* rw) {
    window = rw;
}

StateManager::~StateManager() {
    delete state;
}

void StateManager::Init(GameState* start) {
    running = true;
    state = start;
    state->Init(this);
}

void StateManager::ChangeState(GameState* toState) {
	if (state != toState) {
        delete state;
		state = toState;
        state->Init(this);
	}
}

void StateManager::HandleEvents() {
    state->HandleEvents(this);
}

void StateManager::Update() {
    state->Update(this);
}

void StateManager::Render() {
    window->clear();
    state->Render(this);
    window->display();
}

bool StateManager::Running() {
    return running;
}

void StateManager::Quit() {
    running = false;
}