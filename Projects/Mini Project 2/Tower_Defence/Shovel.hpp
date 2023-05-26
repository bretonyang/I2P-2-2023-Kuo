
#ifndef SHOVEL_HPP
#define SHOVEL_HPP

#include <allegro5/base.h>
#include <list>
#include <string>

#include "Turret.hpp"

class Shovel : public Turret {
public:
    static const int Price;
    Shovel(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // SHOVEL_HPP
