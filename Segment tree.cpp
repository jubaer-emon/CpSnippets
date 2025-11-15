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
ll T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees

// p is the node/segment
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
        T[p] = min(T[p*2], T[p*2 + 1]);
    }
}

//update node u -> val
void update(ll p, ll u, ll val, ll L, ll R){
    if (L == R){
        T[p] = val;
    }
    else{
        ll mid = (L+R)/2;
        //we are only updating 1 index... so just go the right direction
        if (u <= mid)
            update(p*2, u, val, L, mid);
        else
            update(p*2+1, u, val, mid +1, R);
        T[p] = min(T[p*2], T[p*2 + 1]);
    }
}

ll query(ll p, ll ql, ll qr, ll L, ll R){
    // [ql...qr] is outside [L...R]
    if (ql > qr)
        return INF; //returns INF so, doesn't hamper with other part values

    if (ql == L && qr == R)
        return T[p];

    ll mid = (L+R)/2;
    ll left = query(p*2, ql, min(qr, mid), L, mid);
    ll right = query(p*2+1, max(ql, mid+1), qr, mid+1, R);
    /// now combine from left and right.. this is the combine function part
    return min(left, right);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n+1);
    for(ll i = 1; i <= n; i++)
        cin >> a[i];

    build(a, 1, 1, n);  //build Segment Tree

    ll op, u, v;
    while(q--){
        cin >> op >> u >> v;
        //update or query
        if (op == 1)
            update(1, u, v, 1, n);
        else
            cout << query(1, u, v, 1, n) << endl;
    }
    return 0;
}
