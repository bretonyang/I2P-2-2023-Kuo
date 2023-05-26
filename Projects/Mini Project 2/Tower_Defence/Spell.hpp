#ifndef SPELL_HPP
#define SPELL_HPP

#include <allegro5/base.h>
#include <list>
#include <string>

#include "Turret.hpp"

class Spell : public Turret {
public:
    static const int Price;
    static const int SpellDuration = 8; // seconds
    Spell(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
    void Draw() const override;
};

#endif // SPELL_HPP
