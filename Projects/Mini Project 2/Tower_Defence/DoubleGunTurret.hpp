#ifndef DOUBLEGUNTURRET_HPP
#define DOUBLEGUNTURRET_HPP

#include "Turret.hpp"

class DoubleGunTurret : public Turret {
public:
    static const int Price;
    DoubleGunTurret(float x, float y);
    void CreateBullet() override;
};

#endif // DOUBLEGUNTURRET_HPP
