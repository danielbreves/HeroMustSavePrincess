//
//  Animation.cpp
//  HeroMustSavePrincess
//
//  Created by Daniel Breves on 21/10/12.
//  Copyright (c) 2012 Daniel Breves. All rights reserved.
//

#include "Animation.h"

Animation::Animation() {
    currFrame = 0;
    ticks = clock.getElapsedTime();
}

void Animation::AddFrame(sf::IntRect image, sf::Uint32 duration) {
    Frame frame = {image, duration};
    frames.push_back(frame);
}

void Animation::Update() {
    sf::Int32 now = clock.getElapsedTime().asMilliseconds();
    if (frames.size() > 0 && now - ticks.asMilliseconds() > frames[currFrame].duration) {
        if (currFrame < frames.size() - 1) {
            currFrame++;
        } else {
            currFrame = 0;
        }

        ticks = clock.getElapsedTime();
    }
}

void Animation::Draw(sf::RenderWindow* rw, const sf::Texture* texture, const sf::Vector2i position) {
    sf::Sprite frame = sf::Sprite(*texture, frames[currFrame].image);
    frame.setPosition(position.x,position.y);
    rw->draw(frame);
}