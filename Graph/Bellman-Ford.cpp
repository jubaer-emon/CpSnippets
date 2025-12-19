dist = vector<PII>(n+1);

dist[1] = {0, 0};
for (ll i = 2; i <= n; i++)
    dist[i] = {INF, 0};

for (ll i = 1; i <= n; i++){
    for (Edge e: edges){
        if (e.w + dist[e.u].ff < dist[e.v].ff)
            dist[e.v] = {e.w + dist[e.u].ff, e.u}; // u -> v edge
    }
}

bool neg_cyc = false;
ll neg_node = 0;
//check if a negative cycle exists
for (Edge e: edges){
    if (e.w + dist[e.u].ff < dist[e.v].ff){
        dist[e.v] = {e.w + dist[e.u].ff, e.u};
        neg_cyc = true;
        neg_node = e.v;
        //break;
    }
}

// Negative Cycle Path
if (neg_cyc){
    /// IMPORTANT STEP TO NOT GET INTO INFINITE LOOP
    for (ll i = 0; i < n; i++)
        neg_node = dist[neg_node].ss;

    stack<ll> path;
    path.push(neg_node);
    ll tmp_node = dist[neg_node].ss;
    while (tmp_node != neg_node){
        path.push(tmp_node);
        tmp_node = dist[tmp_node].ss;
    }
    path.push(neg_node);
}
