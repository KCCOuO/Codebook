Given a tree of n nodes, your task is to count the number of distinct paths that have at least k_1 and at most k_2 edges.
Input
The first input line contains three integers n, k_1 and k_2: the number of nodes and the path lengths. The nodes are numbered 1,2,\ldots,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Output
Print one integer: the number of paths.
Constraints

1 \le k_1 \le k_2 \le n \le 2 \cdot 10^5
1 \le a,b \le n

Example
Input:
5 2 3
1 2
2 3
3 4
3 5

Output:
6
#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define F first
#define S second
//#define int long long
#define MAXN (int)2e5 + 5
 
struct BIT{
    int n;
    vector<long long> bit;
    void initial(int _n){
        n = _n;
        bit.resize(n + 5, 0);
    }
    void upd(int x, long long val){
        x++;
        for(; x <= n; x += x & -x) bit[x] += val;
    }
    long long query(int x){
        x++;
        long long ans = 0;
        for(; x > 0; x -= x & -x) ans += bit[x];
        return ans;
    }
}bit;
 
int n, k1, k2;
vector<int> g[MAXN];
bool removed[MAXN];
int sz[MAXN];
long long ans = 0;
void dfs_sz(int x, int p)
{
    sz[x] = 1;
    for(int i : g[x]){
        if(i == p or removed[i]) continue;
        dfs_sz(i, x);
        sz[x] += sz[i];
    }
}
int dfs_centroid(int x, int p, int tot)
{
    for(int i : g[x]){
        if(i == p or removed[i]) continue;
        if(sz[i] > (tot >> 1)) return dfs_centroid(i, x, tot);
    }
    return x;
}
void dfs_dis(int x, int p, int d, vector<int> &dis)
{
    if(d > k2) return;
    dis.pb(d);
    for(int i : g[x]){
        if(i == p or removed[i]) continue;
        dfs_dis(i, x, d + 1, dis);
    }
}
vector<int> dis, used, cnt(MAXN, 0);
void decompose(int x)
{
    dfs_sz(x, -1);
    int c = dfs_centroid(x, -1, sz[x]);
    removed[c] = true;
    used.clear();
    bit.upd(0, 1);
    cnt[0]++;
    used.pb(0);
    for(int i : g[c]){
        if(removed[i]) continue;
        dis.clear();
        dfs_dis(i, c, 1, dis);
 
        for(int d : dis){
            if(k2 >= d) ans += bit.query(k2 - d) - bit.query(k1 - d - 1);
        }
        /*
        k2 >= d + x >= k1
        k2 - d >= x >= k1 - d
        */
        for(int d : dis){
            bit.upd(d, 1);
            cnt[d]++;
            if(cnt[d] == 1) used.pb(d);
        }
    }
    for(int i : used) bit.upd(i, -cnt[i]);
    for(int i : used) cnt[i] = 0;
 
    for(int i : g[c]){
        if(!removed[i]){
            decompose(i);
        }
    }
}
signed main()
{
    KCC
    cin >> n >> k1 >> k2;
    for(int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    // cnt.assign(k + 1, 0);
    bit.initial(k2 + 1);
    decompose(1);
    cout << ans << "\n";
    return 0;
}