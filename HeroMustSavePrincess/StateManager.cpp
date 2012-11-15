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
    if (!music.openFromFile(resourcePath() + "Midiman.ogg"))
        exit(EXIT_FAILURE);
    
    PlayMusic();
    
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

void StateManager::PlayMusic() {
    music.play();
}

void StateManager::StopMusic() {
    music.stop();
}

void StateManager::ChangeState(GameState* toState) {
	if (toState != prev) {
        delete prev;
	}
    
    prev = current;
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