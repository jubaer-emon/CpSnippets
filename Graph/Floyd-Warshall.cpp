// Floyd-Warshall
for (ll k = 1; k <= n; k++){
    for (ll i = 1; i <= n; i++){
        for (ll j = 1; j <= n; j++){
            ll alt_dist = dist[i][k] + dist[k][j];
            if (alt_dist < dist[i][j]){
                dist[i][j] = alt_dist;
                dist[j][i] = alt_dist;
            }
        }
    }
}