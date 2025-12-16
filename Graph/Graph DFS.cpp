vector<bool> vis;
vvl adj;
//vl topo;
void dfs(ll u){
    vis[u] = true;
    for (auto &v: adj[u]){
        if (vis[v])
            dfs(v);
    }
    //topo.push_back(u);
}