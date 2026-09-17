// 4.2 Min Cut [d41d8c]
// 需搭配 Salmon 4.1 Dinic<T>（d.g[u] = 邊編號、d.e[id] = {to, f, cap}、d.work(s, t)）
// 0-indexed, s = 0, t = n - 1, 輸出割邊 (1-indexed)
void minCut(int n, int m, Dinic<int> d) {
    int ans = d.work(0, n - 1);
    vector<int> vis(n);
    auto dfs = [&](auto self, int u) -> void {
        if (vis[u]) return; // 原文為 continue，lambda 內無法編譯，改為 return
        vis[u] = 1;
        for (int id : d.g[u]) {
            auto [to, f, cap] = d.e[id];
            if (cap - f > 0) self(self, to);
        }
    };
    dfs(dfs, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) continue;
        for (int id : d.g[i]) {
            if (id & 1) continue;
            auto e = d.e[id];
            if (!vis[e.to])
                cout << i + 1 << " " << e.to + 1 << "\n";
        }
    }
}
