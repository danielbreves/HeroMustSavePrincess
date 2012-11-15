//
//  MenuState.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "StateManager.h"
#include "MessageState.h"
#include "GameState.h"
#include "MenuState.h"
#include "AboutState.h"
#include "Engine.h"


void MenuState::Init(StateManager* manager) {
    int titleSize = 60;
    int optionSize = 24;
    
    // Load from a font file on disk
    if (!bebasneue.loadFromFile(resourcePath() + "bebasneue.ttf"))
    {
        printf("Could not load bebasneue.ttf\n");
        manager->Quit();
    }
    
    // Load from a font file on disk
    if (!silkworm.loadFromFile(resourcePath() + "silkworm.ttf"))
    {
        printf("Could not load silkworm\n");
        manager->Quit();
    }
    
    title = sf::Text("HERO MUST\nSAVE PRINCESS", bebasneue, titleSize);
    menuOptions.push_back(sf::Text("PLAY", silkworm, optionSize));
    menuOptions.push_back(sf::Text("ABOUT", silkworm, optionSize));
    menuOptions.push_back(sf::Text("EXIT", silkworm, optionSize));
    
    sf::Vector2u windowSize = manager->GetWindow()->getSize();
    
    CreateLayout(windowSize);
    
    selected = 0;
}

void MenuState::CreateLayout(sf::Vector2u windowSize) {
    int titlePadding = 50;
    int optionPadding = 15;
    
    int yMenu = (windowSize.y - title.getGlobalBounds().height - titlePadding - menuOptions.size() * (menuOptions[0].getGlobalBounds().height + optionPadding) )/2;
    
    title.setPosition((windowSize.x - title.getGlobalBounds().width)/2, yMenu);
    title.setColor(sf::Color(255, 0, 0));
    title.setStyle(sf::Text::Bold);
    
    yMenu += title.getGlobalBounds().height + titlePadding;
    
    for (int i = 0; i < menuOptions.size(); i++ ) {
        menuOptions[i].setPosition((windowSize.x - menuOptions[i].getGlobalBounds().width)/2, yMenu);
        
        yMenu += menuOptions[i].getGlobalBounds().height + optionPadding;
    }
}

void MenuState::HandleEvents(StateManager* manager) {
    sf::Event evt;

	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
        
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape)) {
			manager->Quit();
		}
        
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Up)) {
			if (selected != 0) {
                selected--;
            }
		}
        
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Down)) {
			if (selected < menuOptions.size() - 1) {
                selected++;
            }
		}
        
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Return)) {
            sf::Vector2u windowSize = manager->GetWindow()->getSize();
               
			switch (selected) {
                case 0:
                    manager->ChangeState(new MessageState("Level 1", 60, new Engine(windowSize.x,windowSize.y)));
                    break;
                case 1:
                    manager->ChangeState(new AboutState);
                    break;
                case 2:
                    manager->Quit();
                    break;
                    
                default:
                    break;
            }
		}
	}
}

void MenuState::Update(StateManager* manager) {
    for (int i = 0; i < menuOptions.size(); i++ ) {
        if (i == selected) {
            menuOptions[i].setColor(sf::Color(0, 255, 0));
        } else {
            menuOptions[i].setColor(sf::Color(255, 255, 255));
        }
    }
}

void MenuState::Render(StateManager* manager) {
    manager->GetWindow()->draw(title);
    
    for (int i = 0; i < menuOptions.size(); i++ ) {        
        manager->GetWindow()->draw(menuOptions[i]);
    }
}

