//
//  Sprite.h
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#ifndef __HeroMustSavePrincess__Sprite__
#define __HeroMustSavePrincess__Sprite__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "ImageManager.h"
#include "Camera.h"
#include "ResourcePath.hpp"
using namespace std;

class Sprite {
    sf::Texture* image;
    static std::auto_ptr<sf::Texture> blood;
    sf::Vector2i position;
    int speed;
    int lastCamPositionX = 0;
    int lastCamPositionY = 0;
    bool visible = true;
    int life = 3;
    
public:
    enum ActionType {NORTH, SOUTH, EAST, WEST, DIE};
    
    Sprite(sf::Texture &img, sf::Vector2i p, int w, int h, int speed);
    ~Sprite();
    void AddAnimation(ActionType action, Animation* animation);
    void CreateAnimations(int rows);
    void SetTexture(sf::Texture &img);
    void Move(int x, int y);
    void Action(ActionType direction);
    void Hit();
    void Update(Camera* camera, int tileSize);
    void Draw(sf::RenderWindow* rw);
    const sf::Vector2i GetPosition() const {return position;}
    const int GetHealth() const {return life;}
    const int GetWidth() const {return width;}
	const int GetHeight() const {return height;}
    const bool IsVisible() const {return visible;}
    
protected:
    map<ActionType, Animation*> animations;
    int width, height;
    ActionType currAction;
};

#endif /* defined(__HeroMustSavePrincess__Sprite__) */
