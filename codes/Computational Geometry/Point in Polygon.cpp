#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define F first
#define S second
#define int long long

int x[(int)1e3 + 5], y[(int) 1e3 + 5], n, m;

bool onsegment(pii a, pii b, pii p)
{
    if((a.F - b.F) * (a.S - p.S) != (a.F - p.F) * (a.S - b.S)) return false;
    if(!(min(a.F, b.F) <= p.F and p.F <= max(a.F, b.F))) return false;
    if(!(min(a.S, b.S) <= p.S and p.S <= max(a.S, b.S))) return false;
    return true;
}

signed main()
{
    KCC
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> x[i] >> y[i];
    while(m--){
        int a, b;
        cin >> a >> b;
        pii p = {a, b};
        bool boundary = false;
        int cnt = 0;
        for(int i = 0; i < n; i++){
            pii u = {x[i], y[i]}, v = {x[(i + 1) % n], y[(i + 1) % n]};
            if(onsegment(u, v, p)){
                boundary = true;
                break;
            }
            if(min(u.S, v.S) <= b and b < max(u.S, v.S)){
                /*
                Line u_to_v: 
                    X = u.F + t(v.F − u.F)
                    Y = u.S + t(v.S − u.S)
                b = u.S + t(v.S - u.S)
                t = (b - u.S) / (v.S - u.S)
                X = u.F + (b - u.S) / (v.S - u.S) * (v.F - u.F)
                */
                double X = u.F + 1.0 * (b - u.S) / (v.S - u.S) * (v.F - u.F);
                if(a <= X) cnt++;
            }
        }
        if (boundary) cout << "BOUNDARY\n";
        else if (cnt & 1) cout << "INSIDE\n";
        else cout << "OUTSIDE\n";
    }
}