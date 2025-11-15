#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

//#define sz 5000
#define M 998244353
vector<ll> no_adj[5000];

ll DP[5001][5001];  // k steps; where ended

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ll n, m, k, x, y;
    cin >> n >> m >> k;

    for (ll i = 0; i < n; i++)
        no_adj[i].push_back(i);

    for (ll i = 0; i < m; i++){
        cin >> x >> y;
        x--; y--;
        no_adj[x].push_back(y);
        no_adj[y].push_back(x);
    }

    DP[0][0] = 1;   // initially at 0
    for (ll i = 1; i < n; i++)
        DP[0][i] = 0;   // not at i

    for (ll i = 1; i <= k; i++){
        ll sum = 0;
        //assuming (for any jth node) connected from all nodes
        for (ll j = 0; j < n; j++)
            sum = (sum + DP[i-1][j] ) % M;

        for (ll j = 0; j < n; j++){
            // discount the disconnected (since only ~ M ~ N) to node j paths
            ll remv = 0;
            for (ll o : no_adj[j])
                remv = (remv + DP[i-1][o]) % M;

            DP[i][j] = (sum - remv) % M;
        }
    }

    if (DP[k][0] < 0)
        DP[k][0] += M;
    cout << DP[k][0] << endl;
    return 0;
}
