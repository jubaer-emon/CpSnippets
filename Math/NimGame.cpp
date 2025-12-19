///https://atcoder.jp/contests/abc368/tasks/abc368_f

vector<ll> g(maxN+1, 0);

for (ll i = 2; i <= maxN; i++){
    ll k  = divs[i].size();
    vector<bool> vis(k+2, false);
    for (ll j = 0; j < k; j++)
        vis[g[ divs[i][j] ] ] = true;

    for (ll j = 0; j <= k+1; j++){
        if (!vis[j]){
            g[i] = j;   // THE MEX
            break;
        }
    }
}


ll l;
cin >> l;
ll z = 0;
for (ll i = 0; i < l; i++){
    ll h;
    cin >> h;
    z ^= g[h];
}

if (z == 0)
    cout << "Bruno";
else
    cout << "Anna";