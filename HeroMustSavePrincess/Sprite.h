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
#include "Level.h"
#include "Camera.h"
#include "ResourcePath.hpp"
using namespace std;

class Sprite {
    static std::auto_ptr<sf::Texture> blood;
    int speed;
    bool visible = true;
    int life = 3;
    
public:
    enum ActionType {STAND, NORTH, SOUTH, EAST, WEST, DIE};
    
    Sprite(sf::Texture &img, sf::Vector2i p, int w, int h, int speed);
    ~Sprite();
    void AddAnimation(ActionType action, Animation* animation);
    void CreateAnimations(int rows);
    void SetTexture(sf::Texture &img);
    void Move(Level* level);
    void SetAction(ActionType action);
    void Hit();
    void Update(Camera* camera, Level* level);
    virtual void Draw(sf::RenderWindow* rw, Camera* camera);
    sf::IntRect GetRect();
    const sf::Vector2i GetPosition() const {return position;}
    const int GetHealth() const {return life;}
    const int GetWidth() const {return width;}
	const int GetHeight() const {return height;}
    const int GetSpeed() const {return speed;}
    const bool IsVisible() const {return visible;}
    
protected:
    map<ActionType, Animation*> animations;
    int width, height;
    ActionType prevAction;
    ActionType currAction;
    sf::Texture* image;
    sf::Vector2i position;
    int xVel = 0, yVel = 0;
};

#endif /* defined(__HeroMustSavePrincess__Sprite__) */
