#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <utility>
#include <allegro5/base.h>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Spell.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int Spell::Price = 100;

Spell::Spell(float x, float y) :
    Turret("play/floor.png", "play/spell.png", x, y, 300, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
    type = "spell";
    isSpell = true;
}

void Spell::CreateBullet() {
    // empty
}

void Spell::Update(float deltaTime) {
    Sprite::Update(deltaTime);
}

void Spell::Draw() const {
    if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	Sprite::Draw();
}

