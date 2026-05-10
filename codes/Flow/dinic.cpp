struct Dinic{
    struct Edge{
        int to, cap, rev;
    };
    vector<Edge> adj[505];
    vector<int> level, ptr;
    int n;
    Dinic(int _n){
        n = _n;
    }
    void addedge(int u, int v, int w){
        adj[u].pb({v, w, adj[v].size()});
        adj[v].pb({u, 0, adj[u].size() - 1});
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
};