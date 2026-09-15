#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define F first
#define S second
#define int long long
#define ll long long

map<vector<int>, int> id;
int cnt = 0;
int get_id(vector<int> v)
{
    if(!id.count(v)) id[v] = ++cnt;
    return id[v];
}
int dfs(int now, int par, vector<vector<int>> &g)
{
    vector<int> v;
    for(int i : g[now]) if(i != par){
        v.pb(dfs(i, now, g));
    }
    sort(v.begin(), v.end());
    return get_id(v);
}
vector<int> get_center(const vector<vector<int>> &g)
{
    int n = g.size() - 1;
    vector<int> deg(n + 1, 0);
    queue<int> q;
    for(int i = 1; i <= n; i++){
        deg[i] = g[i].size();
        if(deg[i] == 1) q.push(i);
    }
    int remain = n;
    while(remain > 2){
        int t = q.size();
        remain -= t;
        while(t--){
            int x = q.front(); q.pop();
            for(int i : g[x]){
                deg[i]--;
                if(deg[i] == 1) q.push(i);
            }
        }
    }
    vector<int> center;
    while(q.size()){
        int x = q.front(); q.pop();
        center.pb(x);
    }
    return center;
}
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> tree1, tree2;
    tree1.resize(n + 1);
    tree2.resize(n + 1);
    
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        tree1[u].pb(v);
        tree1[v].pb(u);
    }
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        tree2[u].pb(v);
        tree2[v].pb(u);
    }
    vector<int> center1 = get_center(tree1);
    vector<int> center2 = get_center(tree2);
    int h1 = min(dfs(center1[0], 0, tree1), dfs(center1.back(), 0, tree1));
    int h2 = min(dfs(center2[0], 0, tree2), dfs(center2.back(), 0, tree2));
    
    if(h1 != h2) cout << "NO\n";
    else cout << "YES\n";
}