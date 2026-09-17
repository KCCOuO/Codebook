int min_cut(Dinic &d, vector<array<int, 3>> &edges){
    int ans = d.compute_max_flow();
    int n = d.n;
    vector<int> vis(n + 1);
    auto dfs = [&](auto self, int u) -> void {
        if(vis[u]) return;
        vis[u] = 1;
        for(auto &e : d.adj[u])
            if(e.cap > 0) self(self, e.to);
    };
    dfs(dfs, 1);
    for(auto [u, v, w] : edges){
        if(w > 0 and vis[u] and !vis[v])
            cout << u << " " << v << "\n";
    }
    return ans;
}
