ll n, m;
cin >> n >> m;
adj.resize(n+1);
vis.resize(n+1);
rep(i, 0, m){
    ll u, v;
    cin >> u >> v;
    //u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);    // comment out if 1-way
}