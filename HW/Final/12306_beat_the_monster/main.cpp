#include <bits/stdc++.h>

using namespace std;

struct ArrayHasher {
    size_t operator()(const array<int, 3>& a) const {
        size_t h = 0;

        for (auto e : a) {
            h ^= hash<int>{}(e)  + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};

class Game {
    using State = array<int, 3>; // level, HP, monster_HP
private:
    int maxLevel;
    int maxHP;
    int monsterDamage;
    vector<vector<int>> table; // vector of "damage" and "Heal"
    State initState;

    vector<State> neighbors(State s) {
        s[1] -= monsterDamage;
        vector<State> res;

        // ATTACK
        res.push_back({s[0], s[1], s[2] - table[s[0]][0]});

        // HEAL
        int newHP = s[1] + table[s[0]][1];
        if (newHP <= maxHP)
            res.push_back({s[0], newHP, s[2]});
        else
            res.push_back(s);

        // LEVEL-UP
        if (s[0] < maxLevel)
            res.push_back({s[0] + 1, s[1], s[2]});
        else
            res.push_back(s);

        return res;
    }

    bool isGoal(State s) {
        return s[1] > 0 && s[2] <= 0;
    }

    int bfs(State s) {
        // NOTE: using vector<int> as key type for unordered_map requires custom hash function!
        unordered_map<State, int, ArrayHasher> distTo;
        queue<State> q;
        unordered_map<State, bool, ArrayHasher> visited;
        q.push(s);
        distTo[s] = 0;
        visited[s] = true;
        while (!q.empty()) {
            State v = q.front();
            q.pop();
            int distToV = distTo[v];

            if (isGoal(v)) {
                return distToV;
            }

            for (State w : neighbors(v)) {
                if (!visited[w]) {
                    visited[w] = true;
                    distTo[w] = distToV + 1;
                    q.push(w);
                }
            }
        }
        return -1;
    }

public:
    Game(int l, int hp, int mhp, int mdmg, vector<vector<int>> t) :
        maxLevel(l), maxHP(hp), monsterDamage(mdmg), table(t), initState({1, hp, mhp}) {}

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
    cout << g.minStepsToWin() + 1 << endl;

    return 0;
}
