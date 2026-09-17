// 0-indexed, 每點恰一條出邊 f[x]
// cid[x]  : x 所在(或最終到達)的環編號
// pos[x]  : 環上點在環內的位置, 非環點為 -1
// dep[x]  : x 走到環需要幾步 (環上為 0)
// top[x]  : x 第一個走到的環上點
// cyc[c]  : 第 c 個環的點 (依 f 的順序)
// jump(x, k) : 從 x 走 k 步, O(log k)
struct FunctionalGraph {
    int n, cnt;
    vector<int> f, cid, pos, dep, top;
    vector<vector<int>> cyc, up;
    FunctionalGraph(int n) : n(n), cnt(0), f(n), cid(n, -1),
        pos(n, -1), dep(n, -1), top(n, -1) {}
    void addEdge(int u, int v) { f[u] = v; }
    void work() {
        vector<int> vis(n, 0); // 0 未訪 1 在路徑上 2 完成
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            vector<int> path;
            int x = i;
            while (!vis[x]) {
                vis[x] = 1;
                path.push_back(x);
                x = f[x];
            }
            if (vis[x] == 1) { // 找到新環
                cyc.emplace_back();
                int k = find(path.begin(), path.end(), x) - path.begin();
                for (int j = k; j < (int)path.size(); j++) {
                    int y = path[j];
                    pos[y] = j - k;
                    cid[y] = cnt;
                    dep[y] = 0;
                    top[y] = y;
                    vis[y] = 2;
                    cyc[cnt].push_back(y);
                }
                path.resize(k);
                cnt++;
            }
            for (int j = (int)path.size() - 1; j >= 0; j--) {
                int y = path[j];
                dep[y] = dep[f[y]] + 1;
                cid[y] = cid[f[y]];
                top[y] = top[f[y]];
            }
            for (auto y : path) vis[y] = 2;
        }
        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        up.assign(LOG, f);
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i < n; i++)
                up[j][i] = up[j - 1][up[j - 1][i]];
    }
    int jump(int x, long long k) {
        if (k > dep[x]) { // 先走進環, 剩下的在環上取模
            k -= dep[x];
            x = top[x];
            auto &c = cyc[cid[x]];
            return c[(pos[x] + k) % c.size()];
        }
        for (int j = 0; k; j++, k >>= 1)
            if (k & 1) x = up[j][x];
        return x;
    }
    // x 能否走到 y ; 可以的話回傳步數, 否則 -1
    long long dist(int x, int y) {
        if (cid[x] != cid[y]) return -1;
        if (pos[y] == -1) { // y 不在環上: 必須在 x 往環的路上
            if (dep[x] < dep[y]) return -1;
            return jump(x, dep[x] - dep[y]) == y ? dep[x] - dep[y] : -1;
        }
        int t = top[x], sz = cyc[cid[x]].size();
        return dep[x] + ((pos[y] - pos[t]) % sz + sz) % sz;
    }
};