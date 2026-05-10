struct SCC{
    vector<vector<int>> g, rg;
    vector<bool> vis, used;
    vector<int> component, st;
    int component_cnt = 0, n;
    void dfs1(int node){
        vis[node] = true;
        for(int i : g[node]) if(!vis[i]) dfs1(i);
        st.pb(node);
    }
    void dfs2(int node){
        used[node] = true;
        for(int i : rg[node]) if(!used[i]) dfs2(i);
        component[node] = component_cnt;
    }
    SCC(const vector<vector<int>> v){
        n = v.size() - 1;
        g = v;
        rg.resize(n + 1);
        vis.resize(n + 1, false);
        used.resize(n + 1, false);
        component.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) for(int j : v[i]) rg[j].pb(i);
    };
    vector<int> find_component(){
        for(int i = 1; i <= n; i++) if(!vis[i]) dfs1(i);
        reverse(st.begin(), st.end());
        for(int i : st) if(!used[i]){
            component_cnt++;
            dfs2(i);
        }
        return component;
    }
};
