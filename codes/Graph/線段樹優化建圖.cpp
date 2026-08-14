#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define int long long
#define vvi vector<vector<long long>>
#define ll long long
 
const int INF = 2e18;
vector<pii> g[(int)5e5 + 5];

int n, m;
void add(int u, int v, int w)
{
    g[u].pb(pii{v, w});
}
void build(int l, int r, int id)
{
    if(l == r){
        add(l, n + id, 0);
        add(n + id, l, 0);
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, id << 1);
    build(mid + 1, r, id << 1 | 1);
    add(n + id, n + (id << 1), 0);
    add(n + id, n + (id << 1 | 1), 0);
}
// 建立 u -> [ql, qr] 邊權w的有向邊
void update(int l, int r, int id, int ql, int qr, int u, int w)
{
    if(ql <= l and r <= qr){
        add(u, n + id, w);
        return;
    }
    int mid = (l + r) >> 1;
    if(ql <= mid) update(l, mid, id << 1, ql, qr, u, w);
    if(qr > mid) update(mid + 1, r, id << 1 | 1, ql, qr, u, w);
}
int dis[(int)5e5 + 5];
void Dijk()
{
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, 1});
    dis[1] = 0;
    while(q.size()){
        auto[d, x] = q.top(); q.pop();
        if(d > dis[x]) continue;
        for(auto [to, w] : g[x]){
            if(dis[to] > dis[x] + w){
                dis[to] = dis[x] + w;
                q.push({dis[to], to});
            }
        }
    }
}
signed main()
{
    KCC
    cin >> n >> m;
    build(1, n, 1);
    for(int i = 0; i < m; i++){
        int op; cin >> op;
        if(op == 1){
            int u, v, w;
            cin >> u >> v >> w;
            g[u].pb(pii{v, w});
        }
        else{
            int u, l, r, w;
            cin >> u >> l >> r >> w;
            update(1, n, 1, l, r, u, w);
        }
    }      
    for(int i = 1; i <= 5 * n; i++) dis[i] = 1e18;
    Dijk();
    for(int i = 1; i <= n; i++) cout << (dis[i] == 1e18 ? -1 : dis[i]) << " ";
    return 0;
}