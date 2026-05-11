void dfs(int now, int par)
{
	deep[now] = deep[par] + 1;
	p[now][0] = par;
	for(int i : v[now]) if(i != par) dfs(i, now);
	return;
}
int lca(int u, int v)
{
	int x = deep[u], y = deep[v];
	if(x > y){
		swap(u, v);
		swap(x, y);
	}
	y -= x; // x < y
	for(int i = 25; i >= 0; i--) if(y & (1 << i)) v = p[v][i];
	if(u == v) return u;
	for(int i = 25; i >= 0; i--){
		if(p[u][i] != p[v][i]){
			u = p[u][i];
			v = p[v][i];
		}
	}
	return p[u][0];
}
for(int j = 1; j < 30; j++){
    for(int i = 2; i <= n; i++){
        p[i][j] = p[p[i][j - 1]][j - 1];
    }
}