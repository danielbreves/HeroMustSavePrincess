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

Sprite::Sprite(sf::Texture &img, sf::Vector2i p, ActionType action, int w, int h, int speed) {
    image = &img;

    if (!blood.get()) {
        blood.reset(new sf::Texture);
        blood->loadFromFile(resourcePath() + "blood.png");
    }
    
    width = w;
    height = h;
    position = p;
    this->speed = speed;
    
    CreateAnimations(3);
    currAction = action;
}

Sprite::~Sprite() {
    // delete all animations
    map<ActionType, Animation*>::iterator it;
    for (it = animations.begin() ; it != animations.end(); it++) {
        delete (*it).second;
    }
    animations.clear();
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

void Sprite::AddAnimation(ActionType action, Animation* animation) {
    animations[action] = animation;
}

void Sprite::Hit(ActionType action, Level* level) {
    int impact = 10;
    
    switch (action) {
        case WEST: Move(level, -speed * impact, 0);
            break;
        case EAST: Move(level, speed * impact, 0);
            break;
        case NORTH: Move(level, 0, -speed * impact);
            break;
        case SOUTH: Move(level, 0, speed * impact);
            break;
            
        default:
            break;
    }
    
    if (life == 1) SetAction(DIE);
    
    life--;
}

// relative x and y
void Sprite::Move(Level* level, int x, int y) {
    int tileSize = level->GetTileSize();
    Corners tiles = GetTileCollisions(level, position.x + x, position.y + y);
    
    // WEST
    if (x < 0 && position.x > 0) {
        if (tiles.upLeft || tiles.downLeft) {
            SetAction(EAST);
            position.x = (tiles.leftX * tileSize) + width;
        } else {
            position.x += x;
        }
    }
    // EAST
    else if (x > 0 && position.x + width < level->GetWidth() * tileSize) {
        if (tiles.upRight || tiles.downRight) {
            SetAction(WEST);
            position.x = (tiles.rightX * tileSize) - width;
        } else {
            position.x += x;
        }
    }
    // NORTH
    else if (y < 0 && position.y > 0) {
        if (tiles.upLeft || tiles.upRight) {
            SetAction(SOUTH);
            position.y = (tiles.upY * tileSize) + height;
        } else {
            position.y += y;
        }
    }
    // SOUTH
    else if (y > 0 && position.y + height < level->GetHeight() * tileSize) {
        if (tiles.downLeft || tiles.downRight) {
            SetAction(NORTH);
            position.y = (tiles.downY * tileSize) - height;
        } else {
            position.y += y;
        }
    }
}

// absolute x and y
Corners Sprite::GetTileCollisions(Level* level, int x, int y) {
    int downY, upY, leftX, rightX;
    Tile *upLeft, *downLeft, *upRight, *downRight;
    int tileSize = level->GetTileSize();
    
    downY = floor((y + height - 1)/tileSize);
    upY = floor(y/tileSize);
    leftX = floor(x/tileSize);
    rightX = floor((x + width - 1)/tileSize);
    
    upLeft = level->GetTile(1, leftX, upY);
    downLeft = level->GetTile(1, leftX, downY);
    upRight = level->GetTile(1, rightX, upY);
    downRight = level->GetTile(1, rightX, downY);
    
    return {downY, upY, leftX, rightX, upLeft, downLeft, upRight, downRight};
}

void Sprite::CheckSpriteCollisions(const vector<Sprite*>* sprites, Level* level) {
    vector<Sprite*>::const_iterator i;
    for (i = sprites->begin(); i < sprites->end(); i++) {
        if ((*i) != this && (*i)->GetHealth()) {
            int xdist = ((*i)->GetPosition().x + (*i)->GetWidth()/2 +1) - (position.x + width/2);
            int ydist = ((*i)->GetPosition().y + (*i)->GetHeight()/2 +1) - (position.y + height/2);
            
            if (sqrt(xdist*xdist+ydist*ydist) < (*i)->GetWidth()/2 + width/2) {
                HandleCollision(*i, level);
            }
        }
    }
}

void Sprite::HandleCollision(Sprite* sprite, Level* level) {
    switch (currAction) {
        case NORTH: SetAction(SOUTH);
            break;
        case SOUTH: SetAction(NORTH);
            break;
        case EAST: SetAction(WEST);
            break;
        case WEST: SetAction(EAST);
            break;
            
        default:
            break;
    }
}

void Sprite::SetAction(ActionType action) {
    if (currAction != STAND) {
        prevAction = currAction;
    }
    
    if (action == ATTACK) {
        attacking = true;
    } else {
        attacking = false;
        currAction = action;
    }
    
}

void Sprite::Update(Camera* camera, Level* level) {    
    sf::Vector2i camPosition = camera->GetPosition();
    sf::Vector2i camSize = camera->GetSize();
    
    int speed = GetSpeed();
    
    switch (currAction) {
        case WEST: Move(level, -speed, 0);
            break;
        case EAST: Move(level, speed, 0);
            break;
        case NORTH: Move(level, 0, -speed);
            break;
        case SOUTH: Move(level, 0, speed);
            break;
            
        default:
            break;
    }
    
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