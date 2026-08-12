#include<bits/stdc++.h>
using namespace std;
#define KCC ios::sync_with_stdio(0);cin.tie(0);
#define pb push_back
#define pii pair<long long, long long>
#define F first
#define S second
#define int long long

pii arr[(int)2e5 + 5];
int dis(int i, pii w)
{
    return (arr[i].F - w.S) * (arr[i].F - w.S) + (arr[i].S - w.F) * (arr[i].S - w.F);
}
signed main()
{
    KCC
    int n, ans = 8e18, id = 0;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> arr[i].F >> arr[i].S;
    sort(arr, arr + n);
    set<pii> s;// {y, x}
    for(int i = 0; i < n; i++){
        int d = sqrt(ans) + 1;
        while(s.size() > 0 and arr[i].F - arr[id].F >= d){
            s.erase({arr[id].S, arr[id].F});
            id++;
        }
        auto l = s.lower_bound({arr[i].S - d, -1e9});
        auto r = s.lower_bound({arr[i].S + d, 1e9});
        for(auto j = l; j != r; ++j) ans = min(ans, dis(i, *j));
        s.insert({arr[i].S, arr[i].F});
    }
    cout << ans << "\n";
    return 0;   
}