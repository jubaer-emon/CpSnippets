/// NOTICE THE SEGMENT TREE IS Not of actual elements but prefix sums

#include <bits/stdc++.h>
#define ll long long
#define M 1000000007
#define INF 1000000000000000
using namespace std;

///ARRAY is 1-indexed
ll T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees
ll S[1000000];  // lazy

// p is the node/segment
void build(vector<ll> &a, ll p, ll L, ll R){
    S[p] = 0;

    //base case
    if (L == R)
        T[p] = a[L];
    else{
        //let us now divide... i.e: for [1, 4] -> [1,2] + [3,4] or [1,5] -> [1,2] + [3,4,5]
        ll mid = (L+R)/2;
        build(a, p*2, L, mid);
        build(a, p*2+1, mid+1, R);

        /// now combine from left and right.. this is the combine function part
        T[p] = max(T[p*2], T[p*2 + 1]);
    }
}

// lazy push
void push(int p) {
    ll val = S[p];

    //update the (maximums) of children
    T[p*2] += val;
    T[p*2 + 1] += val;

    //pass the lazys to children
    S[p*2] += val;
    S[p*2 + 1] += val;

    //remove the current node lazy
    S[p] = 0;
}

//update node u -> val
void update(ll p, ll ul, ll ur, ll val, ll L, ll R){
    if (ul > ur)
        return;

    if (ul == L && ur == R){
        S[p] += val;
        T[p] += val;
        return;
    }

    push(p);

    ll mid = (L+R)/2;

    update(p*2, ul, min(ur, mid), val, L, mid);    //update left segment
    update(p*2+1, max(ul, mid+1), ur, val, mid +1, R);  //right segment

    T[p] = max(T[p*2], T[p*2 + 1]); //propagate up
}

ll query(ll p, ll ql, ll qr, ll L, ll R){
    // [ql...qr] is outside [L...R]
    if (ql > qr)
        return -INF; // [returns INF so, doesn't hamper with other part values]

    if (ql == L && qr == R)
        return T[p];

    push(p);

    ll mid = (L+R)/2;
    ll left = query(p*2, ql, min(qr, mid), L, mid);
    ll right = query(p*2+1, max(ql, mid+1), qr, mid+1, R);
    /// now combine from left and right.. this is the combine function part
    return max(left, right);
}

int main(){

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n+1);
    vector<ll> pre(n+1);
    pre[0] = 0;
    for(ll i = 1; i <= n; i++){
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }

    build(pre, 1, 1, n);  //build Segment Tree

    ll op, u, v;
    while(q--){
        cin >> op >> u >> v;
        //update or query
        if (op == 1){
            // update prefix sum from u to n
            // previously it was "a[u]" now it will be updated "v"; so (v-a[u]) addition of sum
            update(1, u, n, v - a[u], 1, n);
            a[u] = v;
        }
        else{
            // maximum prefix sum from 1 to between (u & v)
            ll val = query(1, u, v, 1, n);

            // minus prefix sum upto u-1
            if (u > 1)
                val -= query(1, u-1, u-1, 1, n);
            cout << max((ll)0, val) << endl;
        }
    }
    return 0;
}
