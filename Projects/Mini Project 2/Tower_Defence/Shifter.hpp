#ifndef SHIFTER_HPP
#define SHIFTER_HPP

#include <allegro5/base.h>
#include <list>
#include <string>

#include "Turret.hpp"

class Shifter : public Turret {
public:
    static const int Price;
    Shifter(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // SHIFTER_HPP
