//
//  MenuState.cpp
//  Spike6
//
//  Created by Daniel Breves on 18/08/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "StateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "Engine.h"

MenuState::MenuState() {
    menuOptions.push_back("PLAY");
    menuOptions.push_back("ABOUT");
    menuOptions.push_back("EXIT");
    
    selected = 0;
}

MenuState::~MenuState() {
}

void MenuState::Init(StateManager* manager) {

}

void MenuState::HandleEvents(StateManager* manager) {
    sf::Event evt;
	//Loop through all window events
	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape)) {
			manager->Quit();
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Space)) {
			manager->ChangeState(new Engine);
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
			switch (selected) {
                case 0:
                    manager->ChangeState(new Engine);
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
    
}

void MenuState::Render(StateManager* manager) {
    int titleSize = 60;
    int titlePadding = 50;
    int optionSize = 24;
    int optionPadding = 15;
    
    sf::Vector2f windowSize = (sf::Vector2f)manager->GetWindow()->getSize();
    
    sf::Font silkworm, bebasneue;
    
    // Load from a font file on disk
    if (!bebasneue.loadFromFile(resourcePath() + "bebasneue.ttf"))
    {
        printf("Could not load ergob.ttf\n");
        manager->Quit();
    }
    
    // Load from a font file on disk
    if (!silkworm.loadFromFile(resourcePath() + "silkworm.ttf"))
    {
        printf("Could not load silkworm\n");
        manager->Quit();
    }
    
    sf::Text title("HERO MUST\nSAVE PRINCESS", bebasneue, titleSize);
    sf::Text option("Sample", silkworm, optionSize);

    title.setColor(sf::Color(255, 0, 0));
    title.setStyle(sf::Text::Bold);
    
    int yMenu = (windowSize.y - title.getGlobalBounds().height - titlePadding - menuOptions.size() * (option.getGlobalBounds().height + optionPadding) )/2;
    
    title.setPosition((windowSize.x - title.getGlobalBounds().width)/2, yMenu);
    
    manager->GetWindow()->draw(title);
    
    yMenu += title.getGlobalBounds().height + titlePadding;
    
    for (int i = 0; i < menuOptions.size(); i++ ) {        
        sf::Text option(menuOptions[i], silkworm, optionSize);
        
        if (i == selected) {
            option.setColor(sf::Color(0, 255, 0));
        } else {
            option.setColor(sf::Color(255, 255, 255));
        }
        
        option.setPosition((windowSize.x - option.getGlobalBounds().width)/2, yMenu);
        
        manager->GetWindow()->draw(option);
        
        yMenu += option.getGlobalBounds().height + optionPadding;
    }
    
}

