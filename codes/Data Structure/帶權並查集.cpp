struct Weighted_DSU{
    vector<int> parent, dis;
    void initial(int n){
        parent.resize(n + 1);
        dis.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x){
        if(parent[x] != x){
            int tmp = parent[x];
            parent[x] = find(tmp);
            dis[x] += dis[tmp];
        }
        return parent[x];
    }
    void unite(int l, int r, int d){
        int lf = find(l), rf = find(r);
        if(lf != rf){
            parent[lf] = rf;
            dis[lf] = dis[r] - dis[l] + d;
        }
    }
    int query(int l, int r){
        if(find(l) != find(r)) return 1e18;
        return dis[l] - dis[r];
    }
};