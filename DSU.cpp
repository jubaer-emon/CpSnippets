#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define INF 1000000000
#define ff first
#define ss second
#define PII pair<ll, ll>

vector<ll> adj[200005];

ll P[200005];
bool cycle[200005];
ll S[200005];
ll pre[200005];

ll findP(ll n){
    if (n == P[n])
        return n;
    return P[n] = findP(P[n]);
}

void unionP(ll a, ll b){
    ll x = findP(a);
    ll y = findP(b);

    if (b == x)   //already in a chain
        cycle[x] = true;
    else if (a == y)
        cycle[y] = true;

    if (x != y)
        P[y] = x;
}



int main(){

    ll t;
    cin >> t;

    while (t--){
        ll n, x;
        cin >> n;

        for (ll i = 1; i <= n; i++){
            pre[i] = 0;
            S[i] = 0;
            cycle[i] = false;
            P[i] = i;   //initialize
        }

        for (ll i = 1; i <= n; i++){
            cin >> x;
            if (pre[x] == i)    //already visited this edge
                continue;
            pre[i] = x;
            unionP(x, i);
        }

        //for (ll i = 1; i <= n; i++)
        //    cout << findP(P[i]) << " ";

        //cout << "YO" << endl;

        ll unq = 0;
        ll cyc = 0;
        for (ll i = 1; i <= n; i++){
            ll u = findP(i);
            S[u]++;

            if (S[u] == 1)
                unq++;
            if (S[u] == 3 && cycle[u])  //cycle with length more than 2
                cyc++;
        }
        ll mini = cyc;
        if (unq > cyc)
            mini++;
        cout << mini << " " << unq << endl;
    }

    return 0;
}
