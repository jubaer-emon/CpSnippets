// MST returns minimum cost (return -1 if not connected)
ll prim(vector<vector<Edge>> adj){

    ll ret = 0;

    priority_queue<PII, vector<PII>, greater<PII>> PQ;


    vector<bool> taken(adj.size());
    vector<ll> cost(adj.size(), INF);
    PQ.push({0, 1}); //0 distance, 1 node
    cost[1] = 0;

    while (!PQ.empty()){
        PII t = PQ.top();
        PQ.pop();

        if (taken[t.ss])
            continue;
        taken[t.ss] = true;
        ret += t.ff;

        for (Edge e : adj[t.ss]){
            // less weight edge to connect e.v
            if (e.w < cost[e.v])
            {
                PQ.push({e.w,e.v});
                cost[e.v] = e.w;    // update the better cost
            }
        }
    }

    for (ll i = 1; i < adj.size(); i++){
        if (cost[i] == INF){
            ret = -1;
            break;
        }
    }
    return ret;
}