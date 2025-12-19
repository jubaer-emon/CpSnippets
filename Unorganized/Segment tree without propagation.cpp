#include <bits/stdc++.h>
#define ll long long
#define M 1000000007
#define INF 10000000000
using namespace std;

ll MIN(ll a, ll b){
    return a < b ? a : b;
}

ll MAX(ll a, ll b){
    return a > b ? a : b;
}

///ARRAY is 1-indexed
//ll T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees
ll S[1000000];  // we only need lazy information here

// p is the node/segment
/*
void build(vector<ll> &a, ll p, ll L, ll R){
    //base case
    if (L == R)
        T[p] = a[L];
    else{
        //let us now divide... i.e: for [1, 4] -> [1,2] + [3,4] or [1,5] -> [1,2] + [3,4,5]
        ll mid = (L+R)/2;
        build(a, p*2, L, mid);
        build(a, p*2+1, mid+1, R);

        /// now combine from left and right.. this is the combine function part
        //T[p] = MIN(T[p*2], T[p*2 + 1]);
    }
}
*/

//update [ul,ur] by val
/// keep a lazy at that node
void update(ll p, ll val, ll ul, ll ur, ll L, ll R){
    if (ul > ur){
        return;
    }

    if (ul == L && ur == R){
        S[p] += val; //notice we keep (add) lazy in a node
    }
    else{
        ll mid = (L+R)/2;
        update(p*2, val, ul, MIN(ur, mid), L, mid);
        update(p*2+1, val, MAX(ul, mid+1), ur, mid +1, R);
    }
}

///QUERY ONLY RETURNS HOW MUCH ADDED to value from initial
ll query(ll p, ll u, ll L, ll R){
    // [ql...qr] is outside [L...R]
    if (L == R)
        return S[p];

    ll mid = (L+R)/2;
    if (u <= mid)
        return query(p*2, u, L, mid) + S[p];    ///NOTICE THE addition of lazy value of current segment
    else
        return query(p*2+1, u, mid+1, R) + S[p];
}

int main(){
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n+1);
    for(ll i = 1; i <= n; i++)
        cin >> a[i];

    //build(a, 1, 1, n);  //build Segment Tree

    ll op, u, v, w;
    while(q--){
        cin >> op;
        //update or query
        if (op == 1){
            cin >> u >> v >> w; //add w to [u,v]
            update(1, w, u, v, 1, n);
        }
        else{
            cin >> u;
            cout << a[u] + query(1, u, 1, n) << endl;
        }
    }
    return 0;
}
