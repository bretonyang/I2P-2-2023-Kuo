#ifndef ULTRAFIREBULLET_HPP
#define ULTRAFIREBULLET_HPP

#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class UltraFireBullet : public Bullet {
public:
    explicit UltraFireBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};

#endif // ULTRAFIREBULLET_HPP
