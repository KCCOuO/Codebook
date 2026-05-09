#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second


mt19937 rnd(time(0));
const int MAXN = 2e5 + 5;
int left_node[MAXN], right_node[MAXN], priority[MAXN], sz[MAXN], node_cnt = 0, root = 0;
char val[MAXN];
void up(int i)
{
    sz[i] = sz[left_node[i]] + sz[right_node[i]] + 1;
}
void split(int i, int l, int r, int rank)
{
    if(i == 0){
        left_node[r] = right_node[l] = 0;
        return;
    }
    if(sz[left_node[i]] + 1 <= rank){
        right_node[l] = i;
        split(right_node[i], i, r, rank - sz[left_node[i]] - 1);
    }
    else{
        left_node[r] = i;
        split(left_node[i], l, i, rank);
    }
    up(i);
}

int merge(int l, int r)
{
    if(l == 0 or r == 0) return l + r;
    if(priority[l] >= priority[r]){
        right_node[l] = merge(right_node[l], r);
        up(l);
        return l;
    }
    else{
        left_node[r] = merge(l, left_node[r]);
        up(r);
        return r;
    }
}
void out(int i)
{
    if(i == 0) return;
    out(left_node[i]);
    cout << val[i];
    out(right_node[i]);
}
int main()
{
    KCC
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        char c;
        cin >> c;
        priority[++node_cnt] = rnd();
        val[node_cnt] = c;
        sz[node_cnt] = 1;
        root = merge(root, node_cnt);
    }
    while(m--){
        int a, b;
        cin >> a >> b;

        split(root, 0, 0, b);
        int lm = right_node[0];
        int r = left_node[0];

        split(lm, 0, 0, a - 1);
        int l = right_node[0];
        int m = left_node[0];
        
        root = merge(merge(l, r), m);
    }
    out(root);
    return 0;
}