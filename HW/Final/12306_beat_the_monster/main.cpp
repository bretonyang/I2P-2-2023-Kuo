#include <bits/stdc++.h>

using namespace std;

class Game {
    using State = array<int, 3>; // level, HP, monster_HP
private:
    int maxLevel;
    int maxHP;
    int monsterDamage;
    vector<vector<int>> table; // vector of "damage" and "Heal"
    int distTo[16][301][401] = {};
    bool visited[16][301][401] = {};
    State initState;

    vector<State> neighbors(State s) {
        // since player starts first, so we should check playerHP in the following
        s[1] -= monsterDamage;
        vector<State> res;

        // ATTACK
        int monsterHP = max(0, s[2] - table[s[0]][0]);
        if (monsterHP <= 0)
            res.push_back(State{s[0], s[1] + monsterDamage, monsterHP}); // our attack kills monster first
        else if (s[1] > 0)
            res.push_back(State{s[0], s[1], monsterHP});

        // HEAL
        int newHP = s[1] + table[s[0]][1];
        if (newHP > 0 && newHP <= maxHP)
            res.push_back(State{s[0], newHP, s[2]});

        // LEVEL-UP
        if (s[1] > 0) {
            if (s[0] + 1 <= maxLevel)
                res.push_back(State{s[0] + 1, s[1], s[2]});
        }

        return res;
    }

    bool isGoal(State s) {
        return s[1] > 0 && s[2] <= 0;
    }

    int bfs(State s) {
//        unordered_map<State, int, ArrayHasher> distTo;
//        unordered_map<State, bool, ArrayHasher> visited;
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

public:
    Game(int l, int hp, int mhp, int mdmg, vector<vector<int>> t) :
        maxLevel(l - 1), maxHP(hp), monsterDamage(mdmg), table(t), initState({0, hp, mhp}) {}

    int minStepsToWin() {
        return bfs(initState);
    }
};

int main()
{
    int L, HP, MHP, MDMG;
    cin >> L >> HP >> MHP >> MDMG;
    vector<vector<int>> table(L, vector<int>(2));
    for (int i = 0; i < L; i++)
        cin >> table[i][0] >> table[i][1];

    Game g(L, HP, MHP, MDMG, table);
    cout << g.minStepsToWin() << endl;

    return 0;
}
