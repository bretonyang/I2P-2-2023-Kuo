#ifndef DICETWOENEMY_HPP
#define DICETWOENEMY_HPP

#include "Enemy.hpp"
#include "Sprite.hpp"

// enemy id = 3
class DiceTwoEnemy : public Enemy {
private:
    Sprite summonImg;

public:
    DiceTwoEnemy(int x, int y);
    void Update(float deltaTime) override;
	void Draw() const override;
};

#endif // DICETWOENEMY_HPP
