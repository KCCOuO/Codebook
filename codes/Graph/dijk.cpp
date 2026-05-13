priority_queue<pii, vector<pii>, greater<pii>> q;
q.push({0, 1});
dis[1] = 0;
while(q.size()){
    auto[d, x] = q.top(); q.pop();
    if(d > dis[x]) continue;
    for(auto [to, w] : g[x]){
        if(dis[to] > dis[x] + w){
            dis[to] = dis[x] + w;
            q.push({dis[to], to});
        }
    }
}