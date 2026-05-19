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