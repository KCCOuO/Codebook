#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second
#define int long long

pii f(pii a, pii b)
{
    return {b.F - a.F, b.S - a.S};
}
int across(pii a, pii b)
{
    if(a.F * b.S < a.S * b.F) return -1;
    if(a.F * b.S > a.S * b.F) return 1;
    return 0;
}
bool overlap(pii a, pii b, pii c, pii d)
{
    if(a.F == b.F and b.F == c.F and c.F == d.F){
        if(min(a.S, b.S) > max(c.S, d.S) or min(c.S, d.S) > max(a.S, b.S)) return false;
    }
    if(min(a.F, b.F) > max(c.F, d.F) or min(c.F, d.F) > max(a.F, b.F)) return false;
    return true;
}
void solve()
{
    int x1, x2, x3, x4, y1, y2, y3, y4;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
    pii a = {x1, y1};
    pii b = {x2, y2};
    pii c = {x3, y3};
    pii d = {x4, y4};
    int x = across(f(a, b), f(a, c));
    int y = across(f(a, b), f(a, d));
    int z = across(f(c, d), f(c, a));
    int w = across(f(c, d), f(c, b));
    if(x * y < 0 and z * w < 0) cout << "YES\n";
    else if(x * y <= 0 and z * w <= 0 and overlap(a, b, c, d))cout << "YES\n";
    else cout << "NO\n";
}
signed main()
{
    KCC
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}