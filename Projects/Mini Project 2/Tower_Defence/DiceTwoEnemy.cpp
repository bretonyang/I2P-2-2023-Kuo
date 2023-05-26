#include <string>

#include "Enemy.hpp"
#include "PlayScene.hpp"
#include "DiceOneEnemy.hpp"
#include "DiceTwoEnemy.hpp"

DiceTwoEnemy::DiceTwoEnemy(int x, int y) : Enemy("play/dice-2.png", x, y, 25, 30, 40, 10), summonImg("play/dice-1.png", x, y) {
    diceTwoSummonBefore = false;
}

void DiceTwoEnemy::Update(float deltaTime) {
    Enemy::Update(deltaTime);
    summonImg.Position = Position;
    summonImg.Tint = Tint;
}

void DiceTwoEnemy::Draw() const {
    if (diceTwoSummonBefore) {
        summonImg.Draw();
    }
    else {
        Enemy::Draw();
    }
}
