void dfs(int x){
    while(g[x].size()){
        int nxt = g[x].back();
        g[x].pop_back(); 
        dfs(nxt);        
    }
    ans.pb(x);        // 倒序記錄答案
}