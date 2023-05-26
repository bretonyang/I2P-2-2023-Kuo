
#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "UltraFireBullet.hpp"
#include "Group.hpp"
#include "DoubleGunTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int DoubleGunTurret::Price = 100;

DoubleGunTurret::DoubleGunTurret(float x, float y) :
    Turret("play/tower-base.png", "play/turret-2.png", x, y, 320, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
    type = "doubleGunTurret";
}

void DoubleGunTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();

    float m = diff.y / diff.x;
    Engine::Point v = Engine::Point(-1.0 / sqrt(1 + m * m), m / sqrt(1 + m * m));
    Engine::Point normV = v.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new UltraFireBullet(Position + normV * 8 + normalized * 36, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new UltraFireBullet(Position - normV * 8 + normalized * 36, diff, rotation, this));
    AudioHelper::PlayAudio("gun.wav");
}
