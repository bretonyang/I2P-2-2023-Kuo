
#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Shovel.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int Shovel::Price = 0;

Shovel::Shovel(float x, float y) :
    Turret("play/floor.png", "play/shovel.png", x, y, 300, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
    isShovel = true;
    type = "shovel";
}

void Shovel::CreateBullet() {
    // empty
}

void Shovel::Update(float deltaTime) {
    Sprite::Update(deltaTime);
}

void Shovel::Draw() const {
	Sprite::Draw();
}
