#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "function.h"

using namespace std;

vector<int> graph::bfs(int source) const
{
    vector<bool> visited(n, false);
    vector<int> distTo(n, 0);
    queue<int> q;

    distTo[source] = 0;
    visited[source] = true;
    q.push(source);

    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        for (int neighbor : adjacent_lists[vertex]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
                distTo[neighbor] = distTo[vertex] + 1;
            }
        }
    }
    return distTo;
}

int tree::diameter() const
{
    // TODO: Find the diameter by BFS traversal.
    vector<int> distTo = bfs(0);
    int farthest_node = 0;
    for (int i = 0; i < n; i++) {
        farthest_node = (distTo[i] > distTo[farthest_node]) ? i : farthest_node;
    }
    distTo = bfs(farthest_node);
    return *max_element(begin(distTo), end(distTo));
}
