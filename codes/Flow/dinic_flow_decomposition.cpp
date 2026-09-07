struct Dinic{
    struct Edge{
        int to, cap, rev;
    };
    vector<vector<Edge>> adj, adj_copy;
    vector<int> level, ptr;
    int n;
    Dinic(int _n){
        n = _n;
        level.resize(n + 1);
        ptr.resize(n + 1);
        adj.resize(n + 1);
        adj_copy.resize(n + 1);
    }
    void addedge(int u, int v, int w){
        adj[u].pb({v, w, adj[v].size()});
        adj_copy[u].pb({v, w, 1});
        
        adj[v].pb({u, 0, adj[u].size() - 1});
        adj_copy[v].pb({u, 0, 0});
    }
    bool bfs(int s, int t)
    {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while(q.size()){
            int x = q.front(); q.pop();
            for(auto edge : adj[x]){
                if(edge.cap > 0 and level[edge.to] == -1){
                    level[edge.to] = level[x] + 1;
                    q.push(edge.to);
                }
            }
        }
        return (level[t] != -1);
    }
    int dfs(int now, int t, int pushed)
    {
        if(now == t) return pushed;
        for(int &i = ptr[now]; i < adj[now].size(); i++){
            auto &w = adj[now][i];
            if(level[now] + 1 != level[w.to] or w.cap == 0) continue;
            int tr = dfs(w.to, t, min(pushed, w.cap));
            if(tr == 0) continue;
            w.cap -= tr;
            adj[w.to][w.rev].cap += tr;
            return tr;
        }
        return 0;
    }
    int compute_max_flow(){
        int max_flow = 0;
        while(bfs(1, n)){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(1, n, 1e18)){
                max_flow += pushed;
            }
        }
        return max_flow;
    }
    
    
    // --- Flow Decomposition ---
    struct FlowEdge {
        int to, flow;
    };
    vector<vector<FlowEdge>> fg;
    vector<int> level_dec, ptr_dec;
    vector<vector<int>> flow_decomposition_ans;

    bool bfs_dec(int s, int t) {
        fill(level_dec.begin(), level_dec.end(), -1);
        level_dec[s] = 0;
        queue<int> q;
        q.push(s);
        while(q.size()){
            int x = q.front(); q.pop();
            for(auto &e : fg[x]){
                if(e.flow > 0 && level_dec[e.to] == -1){
                    level_dec[e.to] = level_dec[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return (level_dec[t] != -1);
    }

    int dfs_dec(int now, int t, int pushed, vector<int> &path) {
        if(now == t) return pushed;
        for(int &i = ptr_dec[now]; i < fg[now].size(); i++){
            auto &e = fg[now][i];
            if(level_dec[now] + 1 != level_dec[e.to] || e.flow == 0) continue;
            
            int tr = dfs_dec(e.to, t, min(pushed, e.flow), path);
            if(tr == 0) continue;
            
            e.flow -= tr;
            path.pb(now);
            return tr;
        }
        return 0;
    }

    void decomposition(){
        fg.resize(n + 1);
        level_dec.resize(n + 1);
        ptr_dec.resize(n + 1);

        for(int i = 1; i <= n; i++){
            for(int j = 0; j < adj[i].size(); j++){
                if(adj_copy[i][j].rev == 0) continue;
                int f = adj_copy[i][j].cap - adj[i][j].cap;
                if(f > 0) fg[i].pb({adj_copy[i][j].to, f});
            }
        }
        
        while(bfs_dec(1, n)){
            fill(ptr_dec.begin(), ptr_dec.end(), 0);
            while(true){
                vector<int> path;
                int pushed = dfs_dec(1, n, 1e18, path);
                if(pushed == 0) break;
                
                reverse(path.begin(), path.end());
                path.pb(n);
                path.pb(pushed); // path.back() 是流量
                
                flow_decomposition_ans.pb(path);
            }
        }
    }
};