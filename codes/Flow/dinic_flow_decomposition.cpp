struct dinic{
    struct edge{
        int to, cap, rev;
    };
    vector<vector<edge>> adj;
    vector<int> level, ptr;
    int n;
    vector<vector<int>> fwd;
    dinic(int _n){
        n = _n;
        level.resize(n+1);
        ptr.resize(n+1);
        adj.resize(n+1);
        fwd.resize(n+1);
    }
    void addedge(int u, int v, int w){
        fwd[u].push_back({adj[u].size()});
        adj[u].push_back({v, w, adj[v].size()});
        adj[v].push_back({u, 0, adj[u].size()-1});
    }
    bool bfs(int s, int t){
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
    int dfs(int now, int t, int pushed){
        if(now == t) return pushed;
        for(int &i = ptr[now]; i<adj[now].size(); i++){
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
    int compute(){
        int max_flow = 0;
        while(bfs(1,n)){
            fill(ptr.begin(), ptr.end(), 0);
            while(int pushed = dfs(1, n, 1e18)){
                max_flow += pushed;
            }
        }
        return max_flow;
    }

    int &flowof(int u, int idx){
        auto &e = adj[u][idx];
        return adj[e.to][e.rev].cap;
    }
    // flow, path
    vector<pair<int, vector<int>>> decompose(int s, int t){
        vector<pair<int, vector<int>>> paths;
        vector<int> cur(n+1, 0), pos(n+1);
        while(true){
            vector<int> path = {s};
            vector<pair<int,int>> used; //u idx
            fill(pos.begin(), pos.end(), -1);
            pos[s] = 0;
            int u=s;
            bool cycle = false;
            while(u != t){
                while(cur[u] < fwd[u].size() and flowof(u, fwd[u][cur[u]]) == 0) cur[u]++;
                if(cur[u] == fwd[u].size()) break;
                int idx = fwd[u][cur[u]];
                int v = adj[u][idx].to;
                used.push_back({u, idx});
                if(pos[v] != -1){ cycle = true; u = v; break; }
                pos[v] = path.size();
                path.push_back(v);
                u = v;
            }
            if(used.empty()) break;
            int start = cycle ? pos[u] : 0;
            int x = LLONG_MAX;
            for(int i= start; i<used.size(); i++) x = min(x, flowof(used[i].first, used[i].second));
            for(int i= start; i<used.size(); i++) flowof(used[i].first, used[i].second) -=x;
            if(!cycle) paths.push_back({x, path});
        }
        return paths;
    }
};