struct Edge{
    ll v, w;
    Edge(ll _v, ll _w){
        v = _v;
        w = _w;
    }
};

vector<vector<Edge>> front_adj;
//vector<vector<Edge>> rev_adj;
//bool visited[100005];


void djikstra(vector<ll> &dist, ll s, vector<vector<Edge>> adj=front_adj){
    /// s is the source

    priority_queue<PII, vector<PII>, greater<PII>> PQ;
    dist[s] = 0;
    PQ.push({0, s}); //0 distance, 1 is the city

    while (!PQ.empty()){
        PII t = PQ.top();
        PQ.pop();

        if (dist[t.ss] != t.ff) //if not equal, that means this t node is old
            continue;

        for (Edge e : adj[t.ss]){
            if (e.w + t.ff < dist[e.v])
            {
                dist[e.v] = e.w + t.ff;
                PQ.push({dist[e.v],e.v});
            }
        }
    }
}