struct max_flow{
    int n;
    vector<int> dis, par, mn;
    vector<vector<int>> g;
    vector<array<int, 3>> edge;
    max_flow(int _n){
        n = _n;
        dis.resize(n + 5);
        par.resize(n + 5);
        mn.resize(n + 5);
        g.resize(n + 5);
    }
    void add_edge(int a, int b, int c){
        g[a].pb(edge.size());
        edge.pb({a, b, c});
        g[b].pb(edge.size());
        edge.pb({b, a, 0});
    }
    int bfs()
    {
        for(int i = 1; i <= n; i++) dis[i] = -1;
        for(int i = 1; i <= n; i++) mn[i] = 1e18;
        dis[1] = 0;
        queue<int> q;
        q.push(1);
        while(q.size()){
            int x = q.front(); q.pop();
            for(int i : g[x]){
                auto [now, to, w] = edge[i];
                if(dis[to] == -1 and w > 0){
                    dis[to] = dis[now] + 1;
                    par[to] = i;
                    mn[to] = min(mn[now], w);
                    q.push(to);
                }
            }
        }
        if(dis[n] == -1) return 0;
        int now = n;
        while(now != 1){
            auto &[a, b, w] = edge[par[now]];
            auto &[ra, rb, rw] = edge[par[now] ^ 1];
            w -= mn[n];
            rw += mn[n];
            now = a;
        }
        return mn[n];
    }
    int max_flow_ans(){
        int ans = 0;
        while(true){
            int t = bfs();
            if(t == 0) break;
            ans += t;
        }
        return ans;
    }
};