void bellman_ford(){
    for(int i = 1; i <= n; i++){
        bool update = false;
        for(int j = 1; j <= n; j++)
            for(auto k : g[j])
                if(dis[k.F] > dis[j] + k.S)
                    update = true, dis[k.F] = dis[j] + k.S;
        if(!update)break;
        if(i == n)cout << "neg_cycle" << "\n";
    }
}