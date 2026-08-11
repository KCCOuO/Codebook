#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define F first
#define S second
#define int long long
 
struct SEG{
    int cnt, len;
}seg[(int)1e7];
void pull(int id, int l, int r)
{
    if(seg[id].cnt > 0) seg[id].len = r - l + 1;
    else{
        if(l != r) seg[id].len = seg[id << 1].len + seg[id << 1 | 1].len;
        else seg[id].len = 0;
    }
}
void update(int ql, int qr, int x, int l, int r, int id)
{
    if(ql <= l and r <= qr) {
        seg[id].cnt += x;
        pull(id, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if(ql <= mid) update(ql, qr, x, l, mid, id << 1);
    if(qr > mid) update(ql, qr, x, mid + 1, r, id << 1 | 1);
    pull(id, l, r);
}
signed main()
{
    KCC
    int n, ans = 0;
    cin >> n;
    vector<array<int, 4>> v;
    for(int i = 0; i < n; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a += 1e6 + 1;
        b += 1e6 + 1;
        c += 1e6 + 1;
        d += 1e6 + 1;
        v.pb({a, b, d, 1});
        v.pb({c, b, d, -1});
    }
    sort(v.begin(), v.end());
    int last = v[0][0], maxval = 2e6 + 1;
    for(auto [x, y1, y2, sign] : v){
        ans += (x - last) * seg[1].len;
        update(y1, y2 - 1, sign, 1, maxval, 1);
        last = x;
    }
    cout << ans << "\n";
    return 0;   
}