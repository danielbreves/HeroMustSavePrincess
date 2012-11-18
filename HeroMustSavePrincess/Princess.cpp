//
//  Princess.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 12/11/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Level.h"
#include "Princess.h"
#include "Princess.h"
#include <algorithm>

Princess::Princess(sf::Texture &img, sf::Vector2i p, int w, int h) {
    image = &img;
    life = 1;
    width = w;
    height = h;
    position = p;
    speed = 1;
    
    if (!blood.get()) {
        blood.reset(new sf::Texture);
        blood->loadFromFile(resourcePath() + "blood.png");
    }
    
    CreateAnimations(3);
    currAction = SOUTH;
}

void Princess::CreateAnimations(int rows) {    
    sf::IntRect image = {0, 0, width, height};
    
    // Create animation SOUTH
    Animation *south = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        south->AddFrame(image, 500);
        image.left += width;
    }
    
    AddAnimation(SOUTH, south);
    
    // Create animation DIE
    Animation *die = new Animation;
    image.top = 0;
    image.left = 0;;
    
    die->AddFrame(image, 1);
    
    AddAnimation(DIE, die);
}

void Princess::Hit(ActionType action, Level* level) {
    level->SetStatus(Level::LOST);
    
    if (life == 1) {
        SetAction(DIE);
        image = &(*blood);
        level->SetStatus(Level::LOST);
    }

    life--;
}

void Princess::Update(Camera* camera, Level* level) {
    sf::Vector2i camPosition = camera->GetPosition();
    sf::Vector2i camSize = camera->GetSize();
    
    if (position.x + width > camPosition.x && position.x < camPosition.x + camSize.x &&
        position.y + height > camPosition.y && position.y < camPosition.y + camSize.y) {
        animations[currAction]->Update();
        visible = true;
    } else {
        visible = false;
    }
}

void Princess::Draw(sf::RenderWindow* rw, Camera* camera) {
    if (visible) {
        animations[currAction]->Draw(rw, image, position - camera->GetPosition());
    }
}