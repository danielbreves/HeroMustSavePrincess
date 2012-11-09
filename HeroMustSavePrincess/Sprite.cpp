//
//  Sprite.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Sprite.h"
#include <time.h>

#define SPRITE_WIDTH    32
#define SPRITE_HEIGHT   32

std::auto_ptr<sf::Texture> Sprite::blood;

Sprite::Sprite(sf::Texture &img, sf::Vector2i p, int w, int h, int speed) {
    image = &img;

    if (!blood.get()) {
        blood.reset(new sf::Texture);
        blood->loadFromFile(resourcePath() + "blood.png");
    }
    
    width = w;
    height = h;
    position = {p.x, p.y};
    this->speed = speed;
    
    CreateAnimations(3);
    currAction = SOUTH;
}

Sprite::~Sprite() {
    // delete all animations
    map<ActionType, Animation*>::iterator it;
    for (it = animations.begin() ; it != animations.end(); it++) {
        delete (*it).second;
    }
    animations.clear();
    
    delete image;
}

void Sprite::CreateAnimations(int rows) {
    sf::IntRect image = {0, 0, width, height};
    
    // Create animation SOUTH
    Animation *south = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        south->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(SOUTH, south);
    
    image.top += height;
    
    // Create animation WEST
    Animation *west = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        west->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(WEST, west);
    
    image.top += height;
    
    // Create animation EAST
    Animation *east = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        east->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(EAST, east);
    
    image.top += height;
    
    // Create animation NORTH
    Animation *north = new Animation;
    image.left = 0;
    
    for (int i = 0; i < rows; i++) {
        north->AddFrame(image, 150);
        image.left += width;
    }
    
    AddAnimation(NORTH, north);
    
    // Create animation DIE
    Animation *die = new Animation;
    image.top = 0;
    image.left = 0;;
    
    die->AddFrame(image, 1);
    
    AddAnimation(DIE, die);
}

void Sprite::SetTexture(sf::Texture &img) {
    image = &img;
}

void Sprite::AddAnimation(ActionType action, Animation* animation) {
    animations[action] = animation;
}

void Sprite::Hit() {
    if (life == 1)
        Action(Sprite::DIE);
    
    life--;
}

void Sprite::Move(int x, int y) {
    position.x += x;
    position.y += y;
}

void Sprite::Action(ActionType direction) {    
    switch (direction) {
        case NORTH:
            position.y -= speed;
            currAction = NORTH;
            break;
        case SOUTH:
            position.y += speed;
            currAction = SOUTH;
            break;
        case EAST:
            position.x += speed;
            currAction = EAST;
            break;
        case WEST:
             position.x -= speed;
            currAction = WEST;
            break;
        case DIE:
            currAction = DIE;
            break;
            
        default:
            break;
    }
}

void Sprite::Update(Camera* camera, int tileSize) {
    // if camera is moving, move sprites in the opposite direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        position.x -= camera->GetPosition().x - lastCamPositionX;
        position.y -= camera->GetPosition().y - lastCamPositionY;
        lastCamPositionX = camera->GetPosition().x;
        lastCamPositionY = camera->GetPosition().y;
    }
    
    if (position.x > -SPRITE_WIDTH && position.x < camera->GetSize().x &&
        position.y > -SPRITE_HEIGHT && position.y < camera->GetSize().y) {
        visible = true;
    } else {
        visible = false;
    }
    
    if (visible && life) animations[currAction]->Update();
}

void Sprite::Draw(sf::RenderWindow* rw) {
    if (visible) {
        if (life) {
            animations[currAction]->Draw(rw, image, position);
        } else {
            animations[currAction]->Draw(rw, &(*blood), position);
        }
    }
}