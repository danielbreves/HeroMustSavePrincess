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

AboutState::AboutState() {

}

AboutState::~AboutState() {
}

void AboutState::Init(StateManager* manager) {
    
}

void AboutState::HandleEvents(StateManager* manager) {
    sf::Event evt;
	//Loop through all window events
	while(manager->GetWindow()->pollEvent(evt))
	{
		if(evt.type == sf::Event::Closed) {
			manager->GetWindow()->close();
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Escape)) {
			manager->ChangeState(new MenuState);
		}
        if(evt.type == sf::Event::KeyPressed && (evt.key.code == sf::Keyboard::Return)) {
            manager->ChangeState(new MenuState);
		}
	}
}

void AboutState::Update(StateManager* manager) {
    
}

void AboutState::Render(StateManager* manager) {
    int titleSize = 60;
    int titlePadding = 50;
    int aboutSize = 20;
    int aboutPadding = 50;
    int backSize = 24;
    int yMenu = 0;
    
    sf::Vector2u windowSize = manager->GetWindow()->getSize();
    
    sf::Font silkworm, bebasneue, arial;
    
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
    
    // Load from a font file on disk
    if (!arial.loadFromFile(resourcePath() + "arial.ttf"))
    {
        printf("Could not load helvetica\n");
        manager->Quit();
    }
    
    sf::Text title("About", bebasneue, titleSize);
    sf::Text about("Find princess Manuella and save her from the\nterrible monsters that have imprisoned her.\nUse the ARROW KEYS to move around and\nhold SPACEBAR to defend yourself.\n\nDeveloped by Daniel Breves.\n\xa9 2012 All Rights Reserved", arial, aboutSize);
    sf::Text back("BACK", silkworm, backSize);
    
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
    
    manager->GetWindow()->draw(title);
    
    manager->GetWindow()->draw(about);
    
    manager->GetWindow()->draw(back);
}