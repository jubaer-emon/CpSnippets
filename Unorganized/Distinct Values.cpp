#include <bits/stdc++.h>
#define ll int
//#define M 1000000007
#define INF 10000000000
using namespace std;

ll MIN(ll a, ll b){
    return a < b ? a : b;
}

ll MAX(ll a, ll b){
    return a > b ? a : b;
}

///ARRAY is 1-indexed
vector<ll> T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees
//each segment will have sorted occurrences of first occurrence of every element belonging to that segment
//if first occurrence is outside segment that means it's unique in that segment

void combine(ll p, ll L, ll M, ll R){
    ll u = 0, v = 0;  // u and v consecutive pointing smallest of 2 child segments
    ll i = 0;

    while (u <= M-L && v <= R-M-1)
    {
        //cout << T[2*p][u] << "W#TF";
        if (T[2*p][u] <= T[2*p+1][v])
            T[p][i++] = T[2*p][u++];
        else
            T[p][i++] = T[2*p+1][v++];
    }

    while (u <= M-L) T[p][i++] = T[2*p][u++];
    while (v <= R-M-1) T[p][i++] = T[2*p+1][v++];
}

// p is the node/segment
void mergesort(vector<ll> &a, ll p, ll L, ll R){
    //base case
    T[p] = vector<ll>(R-L+1);
    ll i = 0;

    if (L == R)
        T[p][i] = a[L];    //just one number
    else{
        //let us now divide... i.e: for [1, 4] -> [1,2] + [3,4] or [1,5] -> [1,2] + [3,4,5]
        ll mid = (L+R)/2;
        mergesort(a, p*2, L, mid);
        mergesort(a, p*2+1, mid+1, R);

        /// now combine from left and right.. this is the combine function part
        combine(p, L, mid, R);
    }

    /*
    cout << L << " x " << R << endl;
    for (ll i = 0; i < R-L+1; i++){
        cout << T[p][i] << " ";
    }
    cout << endl;
    */
}

ll query(ll p, ll ql, ll qr, ll L, ll R, ll k){
    // [ql...qr] is outside [L...R]
    if (ql > qr)
        return 0;

    if (ql == L && qr == R)
        return lower_bound(T[p].begin(), T[p].end(), k) - T[p].begin();


    ll mid = (L+R)/2;
    ll left = query(p*2, ql, min(mid, qr), L, mid, k);
    ll right = query(p*2+1, max(ql, mid+1), qr, mid+1, R, k);
    /// now combine from left and right.. this is the combine function part
    return left+right;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen("test_input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n+1);
    for(ll i = 1; i <= n; i++)
        cin >> a[i];

    map<ll, ll> nums;
    vector<ll> prevs(n+1);

    for (ll i = 1; i <= n; i ++){
        if (nums.find(a[i]) == nums.end()) //not found before
            prevs[i] = -1;
        else
            prevs[i] = nums[a[i]];

        nums[a[i]] = i;
    }

    mergesort(prevs, 1, 1, n);  //build Segment Tree

    ll u, v;
    while(q--){
        cin >> u >> v;
        //query
        cout << query(1, u, v, 1, n, u) << endl;
    }
    return 0;
}
