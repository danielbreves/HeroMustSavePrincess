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

typedef struct {
    int downY, upY, leftX, rightX;
    Tile *upLeft, *downLeft, *upRight, *downRight;
} Corners;

class Sprite {
    
public:
    enum ActionType {STAND, NORTH, SOUTH, EAST, WEST, ATTACK, ATTACK_NORTH, ATTACK_SOUTH, ATTACK_EAST, ATTACK_WEST, DIE};
    
    Sprite() {};
    Sprite(sf::Texture &img, sf::Vector2i p, ActionType action, int w, int h, int speed);
    ~Sprite();
    
    void AddAnimation(ActionType action, Animation* animation);
    virtual void CreateAnimations(int rows);

    virtual void Move(Level* level, int x, int y);
    Corners GetTileCollisions(Level* level, int x, int y);
    void CheckSpriteCollisions(const vector<Sprite*>* sprites, Level* level);
    virtual void HandleCollision(Sprite* sprite, Level* level);
    virtual void Hit(ActionType action, Level* level);
    
    virtual void Update(Camera* camera, Level* level);
    virtual void Draw(sf::RenderWindow* rw, Camera* camera);
    
    void SetTexture(sf::Texture &img);
    void SetAction(ActionType action);
    
    ActionType GetAction() {return currAction;}
    const sf::Vector2i GetPosition() const {return position;}
    const int GetHealth() const {return life;}
    const int GetWidth() const {return width;}
	const int GetHeight() const {return height;}
    const int GetSpeed() const {return speed;}
    const bool IsVisible() const {return visible;}
    
protected:
    map<ActionType, Animation*> animations;
    static std::auto_ptr<sf::Texture> blood;
    int width, height;
    ActionType prevAction;
    ActionType currAction;
    sf::Texture* image;
    sf::Vector2i position;
    bool attacking = false;
    int life = 3;
    int speed;
    bool visible = true;
};

#endif /* defined(__HeroMustSavePrincess__Sprite__) */
