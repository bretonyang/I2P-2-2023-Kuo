#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <set>
#include "function.h"

using namespace std;

template <class T>
void print_sequence(T seq) {
    for (auto i : seq)
        cout << i << ' ';
    cout << endl;
}

// the starting point of your implementation
void Crossing::solve() {
    State initialState{_items};
    initialState.push_back(0);
    initialState.push_back(0);
    initialState.push_back(0);
    initialState.push_back(1);

    map<State, set<list<State>>> pathsToExploredState;

    list<State> initialPath;
    initialPath.push_back(initialState);
    _paths.insert(initialPath);

    while (!_paths.empty()) {
        set<list<State>> newPaths;
        for (list<State> path : _paths) {
            State curState = path.back();

            _explored.insert(curState);
            pathsToExploredState[curState].insert(path);

            set<State> nextStates = extend(curState);

            for (State nextState : nextStates) {
                list<State> potentialNewPath = path;
                potentialNewPath.push_back(nextState);
                if (found(nextState)) {
                    // new solution found
                    _solutions.insert(potentialNewPath);
                }
                else if (_explored.find(nextState) == end(_explored)) {
                    // not explored before
                    newPaths.insert(potentialNewPath);
                }
                else {
                    // nextState explored before
                    // Check if different path && potentialPath does not contain >2 nextState
                    auto check = pathsToExploredState[nextState];
                    if (check.find(potentialNewPath) == end(check)
                        && count(begin(potentialNewPath), end(potentialNewPath), nextState) == 1) {
                        newPaths.insert(potentialNewPath);
                    }
                }
            }
        }

        _paths.clear(); // remove old paths
        _paths.insert(begin(newPaths), end(newPaths)); // insert new paths
    }
}

// extend to other possible states from a certain state
set<State> Crossing::extend(State s) {
    set<State> states;
    for (int w = 0; w <= 1; w++) {
        for (int g = 0; g <= 1; g++) {
            for (int c = 0; c <= 1; c++) {
                if (w + g + c >= 0 && w + g + c <= 1) {
                    State newState = Go(s, w, g, c);
                    if (valid(newState))
                        states.insert(newState);
                }
            }
        }
    }
    return states;
}


// may use s[6] to indicate the direction of move
State Crossing::Go(State s, int wolf, int goat, int cabbage) {
    // s[6] == 1 means currently moving from left to right
    s[0] = s[0] - s[6] * wolf;
    s[1] = s[1] - s[6] * goat;
    s[2] = s[2] - s[6] * cabbage;
    s[3] = s[3] + s[6] * wolf;
    s[4] = s[4] + s[6] * goat;
    s[5] = s[5] + s[6] * cabbage;
    s[6] = -s[6];
    return s;
}

// check the validity of a state
bool Crossing::valid(State s) {
    for (int i = 0; i < 6; i++)  if (s[i] < 0)  return false;
    if (s[6] == -1 && s[0] > s[1] && s[1] > 0) return false;
    if (s[6] == -1 && s[1] > s[2] && s[2] > 0) return false;
    if (s[6] == 1 && s[3] > s[4] && s[4] > 0) return false;
    if (s[6] == 1 && s[4] > s[5] && s[5] > 0) return false;
    return true;
}

// check if all people are at the right bank
bool Crossing::found(State s) {
    return s[0] == 0 && s[1] == 0 && s[2] == 0 && s[6] == -1;
}
