#include <bits/stdc++.h>

using namespace std;


using State = array<int, 3>; // level, HP, monster_HP

int maxLevel;
int maxHP;
int monsterHP;
int monsterDamage;

vector<vector<int>> table(17, vector<int>(2)); // vector of (damage, heal)
int distTo[17][305][405] = {};
bool visited[17][305][405] = {};

vector<State> neighbors(State s) {
    // CAREFUL: player starts first, then monster attack!!!
    vector<State> res;

    // ATTACK
    int monsterHP = max(0, s[2] - table[s[0]][0]);
    if (monsterHP <= 0)
        res.push_back(State{s[0], s[1], monsterHP}); // our attack kills monster first
    else if (s[1] - monsterDamage > 0)
        res.push_back(State{s[0], s[1] - monsterDamage, monsterHP});

    // HEAL (We NEED to calculate healed HP first before attacked by monster)
    // wrong method: I originally calculated player's HP after attacked by monster, then check healing
    int newHP = min(s[1] + table[s[0]][1], maxHP);
    if (newHP - monsterDamage > 0)
        res.push_back(State{s[0], newHP - monsterDamage, s[2]});

    // LEVEL-UP (either way are fine)
    if (s[1] - monsterDamage > 0) {
        int newLevel = min(s[0] + 1, maxLevel);
        res.push_back(State{newLevel, s[1] - monsterDamage, s[2]});
//            if (s[0] + 1 <= maxLevel)
//                res.push_back(State{s[0] + 1, s[1] - monsterDamage, s[2]});
    }

    return res;
}

bool isGoal(State s) {
    return s[1] > 0 && s[2] <= 0;
}

int bfs(State s) {
    /// although using unordred_map is also possible, but it's a lot slower (800ms vs. 80ms)
    /// It actually makes sense, since HashMaps are "amortized" contant vs. "always" constant by arrays

    queue<State> q;
    q.push(s);
    distTo[s[0]][s[1]][s[2]] = 0;
    visited[s[0]][s[1]][s[2]] = true;

    while (!q.empty()) {
        State v = q.front();
        q.pop();
        int distToV = distTo[v[0]][v[1]][v[2]];

        if (isGoal(v)) return distToV;

        for (State w : neighbors(v)) {
            if (!visited[w[0]][w[1]][w[2]]) {
                visited[w[0]][w[1]][w[2]] = true;
                distTo[w[0]][w[1]][w[2]] = distToV + 1;
                q.push(w);
            }
        }
    }
    return -1;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> maxLevel >> maxHP >> monsterHP >> monsterDamage;

    for (int i = 1; i <= maxLevel; i++) {
        cin >> table[i][0] >> table[i][1];
    }

    cout << bfs(State{1, maxHP, monsterHP}) << endl;

    return 0;
}
