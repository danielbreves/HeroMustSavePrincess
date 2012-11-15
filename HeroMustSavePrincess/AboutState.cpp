//
//  AboutState.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//


#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "StateManager.h"
#include "GameState.h"
#include "AboutState.h"
#include "MenuState.h"
#include "Engine.h"

void AboutState::Init(StateManager* manager) {
    if (!bebasneue.loadFromFile(resourcePath() + "bebasneue.ttf"))
    {
        printf("Could not load bebasneue.ttf\n");
        manager->Quit();
    }
    
    if (!silkworm.loadFromFile(resourcePath() + "silkworm.ttf"))
    {
        printf("Could not load silkworm\n");
        manager->Quit();
    }
    
    if (!arial.loadFromFile(resourcePath() + "arial.ttf"))
    {
        printf("Could not load helvetica\n");
        manager->Quit();
    }
    
    sf::Vector2u windowSize = manager->GetWindow()->getSize();
    
    CreateLayout(windowSize);
}

void AboutState::CreateLayout(sf::Vector2u windowSize) {
    int titleSize = 60;
    int titlePadding = 50;
    int aboutSize = 20;
    int aboutPadding = 50;
    int backSize = 24;
    int yMenu = 0;
        
    title = sf::Text("About", bebasneue, titleSize);
    about = sf::Text("Find princess Manuella and save her from the\nterrible monsters that have imprisoned her.\nUse the ARROW KEYS to move around and\nhold SPACEBAR to defend yourself.\n\nDeveloped by Daniel Breves.\n\xa9 2012 All Rights Reserved", arial, aboutSize);
    back = sf::Text("BACK", silkworm, backSize);
    
    title.setColor(sf::Color(255, 0, 0));
    title.setStyle(sf::Text::Bold);
    about.setColor(sf::Color(255, 255, 255));
    back.setColor(sf::Color(0, 255, 0));
    
    yMenu = (windowSize.y - title.getGlobalBounds().height - titlePadding - about.getGlobalBounds().height - aboutPadding - back.getGlobalBounds().height)/2;
    
    title.setPosition((windowSize.x - title.getGlobalBounds().width)/2, yMenu);
    
    yMenu += title.getGlobalBounds().height + titlePadding;
    
    about.setPosition((windowSize.x - about.getGlobalBounds().width)/2, yMenu);
    
    yMenu += about.getGlobalBounds().height + aboutPadding;
    
    back.setPosition((windowSize.x - back.getGlobalBounds().width)/2, yMenu);
}

void AboutState::HandleEvents(StateManager* manager) {
    sf::Event evt;

	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape || evt.key.code == sf::Keyboard::Return)) {
			manager->ChangeState(new MenuState);
		}
	}
}

void AboutState::Update(StateManager* manager) {
    
}

void AboutState::Render(StateManager* manager) {
    manager->GetWindow()->draw(title);
    manager->GetWindow()->draw(about);
    manager->GetWindow()->draw(back);
}