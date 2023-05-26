#include <string>

#include "PlayScene.hpp"
#include "BossEnemy.hpp"

BossEnemy::BossEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 25, 25, 100, 100) {}

void BossEnemy::OnExplode() {
    for (int i = 0; i < 10; i++) {
        getPlayScene()->enemyWaveData.emplace_back(1, 1.5);
    }
}
