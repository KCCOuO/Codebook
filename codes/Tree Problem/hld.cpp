vector<int> edge[MAXN];
int ar[MAXN], sz[MAXN], par[MAXN], son[MAXN], dep[MAXN], dfn[MAXN], top[MAXN], t = 0;
void dfs_son(int x, int p, int d)
{
    sz[x] = 1;
    dep[x] = d;
    son[x] = 0;
    for(int i : edge[x]){
        if(i != p){
            dfs_son(i, x, d + 1);
            sz[x] += sz[i];
            par[i] = x;
            if(sz[i] > sz[son[x]]) son[x] = i;
        }
    }
}
void dfs_hld(int x, int p)
{
    dfn[x] = ++t;
    if(son[x] != 0){
        top[son[x]] = top[x];
        dfs_hld(son[x], x);
    }
    for(int i : edge[x]){
        if(i != p and i != son[x]){
            top[i] = i;
            dfs_hld(i, x);
        }
    }
}
int main()
{
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> ar[i];
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        edge[u].pb(v);
        edge[v].pb(u);
    }
    dfs_son(1, 0, 1);
    top[1] = 1;
    dfs_hld(1, 0);
    
    vector<int> v(n + 5);
    for(int i = 1; i <= n; i++) v[dfn[i]] = ar[i];
    seg_tree seg(n);
    seg.build(v, 1, n, 1);
    while(q--){
        int op; cin >> op;
        if(op == 1){ //change the value of node s to x
            int s, x;
            cin >> s >> x;
            seg.upd(dfn[s], x, 1, n, 1);
        }
        else{ //find the maximum value on the path between nodes a and b.
            int a, b, ans = 0;
            cin >> a >> b;
            while(top[a] != top[b]){
                if(dfn[top[a]] < dfn[top[b]]) swap(a, b);
                ans = max(ans, seg.query(dfn[top[a]], dfn[a], 1, n, 1));
                a = par[top[a]];
            }
            if(dfn[a] > dfn[b]) swap(a, b);
            ans = max(ans, seg.query(dfn[a], dfn[b], 1, n, 1));
            cout << ans << " ";
        }
    }
}