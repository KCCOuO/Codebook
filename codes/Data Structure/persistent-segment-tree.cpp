#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define F first
#define S second
#define int long long
struct st{
    int l, r, sum;
}tree[(int)8e6 + 5];
int root[(int)2e5 + 5], ar[(int)2e5 + 5];
int copy_cnt = 1, cnt = 0;
int build(int l, int r)
{
    int node = ++cnt;
    if(l == r){
        tree[cnt].sum = ar[l - 1];
        return node;
    }
    int mid = (l + r) >> 1;
    tree[node].l = build(l, mid);
    tree[node].r = build(mid + 1, r);
    tree[node].sum = tree[tree[node].l].sum + tree[tree[node].r].sum;
    return node;
}
int upd(int pre, int l, int r, int pos, int val)
{
    int node = ++cnt;
    tree[node] = tree[pre];
    if(l == r){
        tree[node].sum = val;
        return node;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) tree[node].l = upd(tree[pre].l, l, mid, pos, val);
    else tree[node].r = upd(tree[pre].r, mid + 1, r, pos, val);
    tree[node].sum = tree[tree[node].l].sum + tree[tree[node].r].sum;
    return node;
}
int query(int node, int l, int r, int ql, int qr)
{
    if(ql <= l and r <= qr) return tree[node].sum;
    int mid = (l + r) >> 1, re = 0;
    if(ql <= mid) re += query(tree[node].l, l, mid, ql, qr);
    if(qr > mid) re += query(tree[node].r, mid + 1, r, ql, qr);
    return re;
}
signed main()
{
    KCC
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> ar[i];
    root[copy_cnt] = build(1, n);
    while(q--){
        int op, k;
        cin >> op >> k;
        if(op == 1){
            int a, x;
            cin >> a >> x;
            root[k] = upd(root[k], 1, n, a, x);
        }
        if(op == 2){
            int l, r;
            cin >> l >> r;
            cout << query(root[k], 1, n, l, r) << "\n";
        }
        if(op == 3) root[++copy_cnt] = root[k];
    }
    return 0;
}