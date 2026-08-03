struct tarjan_scc{
    int n, dfn_cnt = 0, scc_cnt = 0;
    vector<int> belong, dfn, low, stack;
    vector<vector<int>> g;
    void initial(int _n){
        n = _n;
        belong.resize(n + 1, 0);
        dfn.resize(n + 1, 0);
        low.resize(n + 1, 0);
        g.resize(n + 1, vector<int>(0));
    }
    void addedge(int u, int v){
        g[u].pb(v);
    }
    void tarjan(int u){
        dfn[u] = low[u] = ++dfn_cnt;
        stack.pb(u);
        for(int i : g[u]){
            if(dfn[i] == 0){
                tarjan(i);
                low[u] = min(low[u], low[i]);
            }
            else if(belong[i] == 0){
                low[u] = min(low[u], dfn[i]);
            }
        }
        if(dfn[u] == low[u]){
            scc_cnt++;
            int x;
            do{
                x = stack.back();
                belong[x] = scc_cnt;
                stack.pop_back();
            }while(x != u);
        }
    }
    void work(){
        for(int i = 1; i <= n; i++){
            if(belong[i] == 0){
                tarjan(i);
            }
        }
    }
};