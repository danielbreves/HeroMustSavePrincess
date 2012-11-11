//
//  Sprite.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Sprite.h"
#include <time.h>
#include <math.h>

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
    
    // Create animation STAND
//    Animation *stand = new Animation;
//    stand->AddFrame(image, 150);
//    AddAnimation(STAND, stand);
    
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
        SetAction(DIE);
    
    life--;
}

void Sprite::Move(Level* level) {   
    int downY, upY, leftX, rightX;
    Tile *upLeft, *downLeft, *upRight, *downRight;
    sf::IntRect p = GetRect();
    int tileSize = level->GetTileSize();
    
    if (currAction == WEST && position.x > 0) {
        downY = floor((p.top + p.height - 1)/tileSize);
        upY = floor((p.top)/tileSize);
        leftX = floor((p.left - speed)/tileSize);
        
        upLeft = level->GetTile(1, leftX, upY);
        downLeft = level->GetTile(1, leftX, downY);
        
        if (upLeft || downLeft) {
            SetAction(STAND);
            position.x = (leftX * tileSize) + p.width;
        } else {
            position.x -= speed;
        }
    }
    else if (currAction == EAST && position.x + p.width < level->GetWidth() * tileSize) {
        downY = floor((p.top + p.height - 1)/tileSize);
        upY = floor((p.top)/tileSize);
        rightX = floor((p.left + p.width + speed - 1)/tileSize);
        
        upRight = level->GetTile(1, rightX, upY);
        downRight = level->GetTile(1, rightX, downY);
        
        if (upRight || downRight) {
            SetAction(STAND);
            position.x = (rightX * tileSize) - p.width;            
        } else {
            position.x += speed;
        }
    }
    else if (currAction == NORTH && position.y > 0) {
        upY = floor((p.top - speed)/tileSize);
        leftX = floor(p.left/tileSize);
        rightX = floor((p.left + p.width - 1)/tileSize);
        
        upLeft = level->GetTile(1, leftX, upY);
        upRight = level->GetTile(1, rightX, upY);
        
        if (upLeft || upRight) {
            SetAction(STAND);
            position.y = (upY * tileSize) + p.height;
        } else {
            position.y -= speed;
        }
    }
    else if (currAction == SOUTH && position.y + p.height < level->GetHeight() * tileSize) {
        downY = floor((p.top + p.height + speed - 1)/tileSize);
        leftX = floor(p.left/tileSize);
        rightX = floor((p.left + p.width - 1)/tileSize);
        
        downLeft = level->GetTile(1, leftX, downY);
        downRight = level->GetTile(1, rightX, downY);
        
        if (downLeft || downRight) {
            SetAction(STAND);
            position.y = (downY * tileSize) - p.height;
        } else {
            position.y += speed;
        }
    }
}

void Sprite::SetAction(ActionType action) {
    if (currAction != STAND) prevAction = currAction;
    currAction = action;
}

sf::IntRect Sprite::GetRect() {
    return sf::IntRect(position.x,position.y,width,height);
}

void Sprite::Update(Camera* camera, Level* level) {
    sf::Vector2i camPosition = camera->GetPosition();
    sf::Vector2i camSize = camera->GetSize();
    
    if (position.x + width > camPosition.x && position.x < camPosition.x + camSize.x &&
        position.y + height > camPosition.y && position.y < camPosition.y + camSize.y) {
        visible = true;
    } else {
        visible = false;
    }
    
    if (visible && life && currAction != STAND) animations[currAction]->Update();
}

void Sprite::Draw(sf::RenderWindow* rw, Camera* camera) {
    ActionType animation;
    
    if (currAction == STAND) {
        animation = prevAction;
    } else {
        animation = currAction;
    }
    
    if (visible) {
        if (life) {
            animations[animation]->Draw(rw, image, position - camera->GetPosition());
        } else {
            animations[animation]->Draw(rw, &(*blood), position - camera->GetPosition());
        }
    }
}