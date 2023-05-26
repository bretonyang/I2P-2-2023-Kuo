
#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Shifter.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int Shifter::Price = 0;

Shifter::Shifter(float x, float y) :
    Turret("play/floor.png", "play/shifter.png", x, y, 300, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
    isShifter = true;
    type = "shifter";
}

void Shifter::CreateBullet() {
    // empty
}

void Shifter::Update(float deltaTime) {
    Sprite::Update(deltaTime);
}

void Shifter::Draw() const {
	Sprite::Draw();
}

