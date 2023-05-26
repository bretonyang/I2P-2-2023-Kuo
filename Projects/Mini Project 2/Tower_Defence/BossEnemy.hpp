#ifndef BOSSENEMY_HPP
#define BOSSENEMY_HPP

#include "Enemy.hpp"

// enemy id = 4
class BossEnemy : public Enemy {
protected:
    void OnExplode() override;

public:
    BossEnemy(int x, int y);
};

#endif // BOSSENEMY_HPP
