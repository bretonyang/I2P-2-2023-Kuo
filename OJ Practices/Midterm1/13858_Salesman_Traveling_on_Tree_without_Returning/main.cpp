#include <bits/stdc++.h>

using namespace std;

pair<int,unsigned long long int> node_finding(vector<vector<pair<int,int>>> adj, int n , int idx){
    vector<bool> visited(n, false);
    vector<unsigned long long int> dist(n, 0);
    queue<int> q;
    // first one node in the path
    q.push(idx);
    visited[idx] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto it : adj[u]){
            if(!visited[it.first]){
                visited[it.first] = true;
                dist[it.first] = dist[u] + it.second;
                q.push(it.first);
            }
        }
    }
    unsigned long long int max = 0;
    int path_node = 0;
    for(int i = 0; i < n; i++){
        if(dist[i] > max){
            max = dist[i];
            path_node = i;
        }
    }
    return make_pair(path_node, max);
}

unsigned long long int longestPath(vector<vector<pair<int,int>>> adj, int n){
    pair<int,long long int> u , v;
    u = node_finding(adj, n, 0);
    v = node_finding(adj, n, u.first);

    // use dfs to find path from u to v
    unsigned long long int ans = 0;
    for(auto it : adj){
        for(auto item : it){
            ans += item.second;
        }
    }
    ans -= v.second;
    return ans;
}

int main(){
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n, vector<pair<int,int>>());
    for(int i = 0 ; i < n-1;i++){
        int a, b , w;
        cin >> a >> b >> w ;
        adj[a].push_back(make_pair(b,w));
        adj[b].push_back(make_pair(a,w));
    }
    cout << longestPath(adj, adj.size()) << endl;
}
