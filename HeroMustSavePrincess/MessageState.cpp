//
//  MessageState.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "StateManager.h"
#include "GameState.h"
#include "MessageState.h"

MessageState::MessageState() {
    
}

MessageState::MessageState(std::string msg, int f, GameState* next) {
    message = msg;
    frames = f;
    nextState = next;
}

MessageState::~MessageState() {
}

void MessageState::Init(StateManager* manager) {
    
}

void MessageState::HandleEvents(StateManager* manager) {
    sf::Event evt;
	//Loop through all window events
	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
    }
}

void MessageState::Update(StateManager* manager) {
    frames--;
    
    if (!frames) {
        manager->ChangeState(nextState);
    }
}

void MessageState::Render(StateManager* manager) {    
    sf::Vector2u windowSize = manager->GetWindow()->getSize();
    
    sf::Font bebasneue;
    
    // Load from a font file on disk
    if (!bebasneue.loadFromFile(resourcePath() + "bebasneue.ttf"))
    {
        printf("Could not load bebasneue.ttf\n");
        manager->Quit();
    }
    
    sf::Text title(message, bebasneue, 80);
    
    title.setColor(sf::Color(255, 255, 255));
    title.setStyle(sf::Text::Bold);
        
    title.setPosition((windowSize.x - title.getGlobalBounds().width)/2, windowSize.y/2 - title.getGlobalBounds().height);
    
    manager->GetWindow()->draw(title);
}