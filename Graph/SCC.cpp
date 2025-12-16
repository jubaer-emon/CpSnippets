struct SCC {
    ll N;
    vvl adj, radj;
    vl topo, comp;   // comp is component of node
    vector<bool> vis;

    vvl groups, condG;
    vector<bool> visSCC;
    vl topoSCC;
    void init(ll _N) {
        N = _N;
        adj.resize(N), radj.resize(N), comp = vl(N, -1), vis.resize(N);
    }
    void add_edge(ll u, ll v) { adj[u].pb(v), radj[v].pb(u); }
    void dfs(ll u) {
        vis[u] = 1;
        for (auto &v: adj[u]) if (!vis[v]) dfs(v);
        topo.pb(u);
    }
    void dfs2(ll u, ll p) {
        comp[u] = p;
        groups[p].pb(u);
        for (auto &v: radj[u]) if (comp[v] == -1) dfs2(v, p);
    }

    void dfsSCC(ll u){
        visSCC[u] = 1;
        for (auto &v: condG[u]) if (!visSCC[v]) dfsSCC(v);
        topoSCC.pb(u);
    }

    void gen(ll _N) {  // fills allComp
        rep(i, 1, _N) if (!vis[i]) dfs(i);
        reverse(all(topo));
        
        ll cid = 0;
        for (auto &u: topo) if (comp[u] == -1){
            groups.pb({});
            dfs2(u, cid++);
        }
        
        // build cond. graph
        condG.resize(cid);
        visSCC.resize(cid);
        rep (i, 1, _N) {
            for (auto &j: adj[i]) {
                if (comp[i] == comp[j]) continue;
                    condG[comp[i]].pb(comp[j]); //duplicate edges
            }
        }

        // topOrder of SCC
        rep(i, 1, _N) if (!visSCC[comp[i]]) dfsSCC(comp[i]);
        reverse(all(topoSCC));
    }
};