struct DSU_rollback{
    int components;
    vector<int> parent, sz;
    struct modify{
        int u, v, pre_sz;
    };
    vector<modify> history;

    void initial(int n){
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        components = n;
        for(int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int x){
        while(x != parent[x]) x = parent[x];
        return x;
    }

    void unite(int u, int v){
        int root_u = find(u), root_v = find(v);
        if(root_u == root_v) return;
        if(sz[root_u] < sz[root_v]) swap(root_u, root_v);
        
        history.pb({root_u, root_v, sz[root_u]});
        parent[root_v] = root_u;
        sz[root_u] += sz[root_v];
        components--;
    }
    void rollback(){
        if(history.size() == 0) return;
        modify last = history.back();
        history.pop_back();

        parent[last.v] = last.v;
        sz[last.u] = last.pre_sz;
        components++;
    }
    int dsutime(){return (int)history.size();}
    void return_to_t(int t){
        while(history.size() > t) rollback();
    }
};