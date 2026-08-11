struct Edge {
    ll to, cap, cost, rev;
    Edge() {}
    Edge(int _to, ll _cap, ll _cost, int _rev) : to(_to), cap(_cap), cost(_cost), rev(_rev) {}
};
vector<Edge> adj[N];
ll dis[N]; int par[N], par_id[N]; bool in_que[N];
pair<ll, ll> MCMF(int s, int t) {
    ll flow = 0, cost = 0;
    while(true) {
        memset(dis, 0x3f, sizeof(dis));
        memset(in_que, 0, sizeof(in_que));
        queue<int> que;
        que.push(s); dis[s] = 0;
        while(!que.empty()) { // SPFA
            int x = que.front();
            que.pop(); in_que[x] = 0;
            for(int i = 0;i < (int)adj[x].size();i++) {
                Edge &e = adj[x][i];
                if(e.cap > 0 && dis[e.to] > dis[x] + e.cost) {
                    dis[e.to] = dis[x] + e.cost;
                    par[e.to] = x;
                    par_id[e.to] = i;
                    if(!in_que[e.to]) {
                        in_que[e.to] = 1;
                        que.push(e.to);
                    }
                }
            }
        }
        if(dis[t] >= INF) break;
        ll mi_flow = INF;
        for(int i = t; i != s; i = par[i])
            mi_flow = min(mi_flow, adj[par[i]][par_id[i]].cap);
        flow += mi_flow, cost += mi_flow * dis[t];
        for(int i = t; i != s; i = par[i]) {
            Edge &e = adj[par[i]][par_id[i]];
            e.cap -= mi_flow;
            adj[e.to][e.rev].cap += mi_flow;
        }
    }
    return make_pair(flow, cost);
}
void add_edge(int a, int b, ll cap, ll cost) {
    adj[a].push_back(Edge(b, cap, cost, (int)adj[b].size()));
    adj[b].push_back(Edge(a, 0, -cost, (int)adj[a].size() - 1));
}
ll hungarian(vector<vector<ll>> cost) {
    int n = (int)cost.size();
    for(int i = 0; i < n;i++) {
        for(int j = 0; j < n;j++) {
            int L = i, T = j + n;
            add_edge(L, T, 1, cost[i][j]);
        }
    }
    int s = 2 * n, t = 2 * n + 1;
    for(int i = 0; i < n;i++) {
        int L = i, T = i + n;
        add_edge(s, L, 1, 0);
        add_edge(T, t, 1, 0);
    }
    // MCMF(s, t)
    for(int i = 0; i < n;i++) {
        for(Edge &e : adj[i]) {
            if(e.to == s) continue;
            int row = i, col = e.to - n;
            if(e.cap == 0) 
                // (row + 1) match (col + 1)
        }
    }
    return MCMF(s, t).second;
}