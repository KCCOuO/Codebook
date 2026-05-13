#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
 
int subtree[(int)2e5 + 5], n;
vector<int> g[(int)2e5 + 5];
void dfs(int now, int par)
{
	subtree[now] = 1;
	for(auto w : g[now]){
		if(w != par){
			dfs(w, now);
			subtree[now] += subtree[w];
		}
	}
	return ;
}
int get(int now, int par)
{
	for(auto w : g[now]){
		if(w != par and subtree[w] * 2 > n) return get(w, now);
	}
	return now;
}
signed main()
{
	KCC
	cin >> n;
	for(int i = 0; i < n - 1; i++){
		int a, b;cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(1, 0);
	cout << get(1, 0) << "\n";
	return 0;
}