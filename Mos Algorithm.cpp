/// https://codeforces.com/contest/2014/problem/H

//a+b = (a^b) + 2*(a&b)
/*
        //iterate through MAP:

        map<ll, vector<ll>> nums;
        for (auto const& ele: nums){
            vector<ll> V = ele.second;
        }


        // ORDERING

        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](ll i, ll j) {
            return b[i] < b[j]; // small b first
        });
*/


#include <bits/stdc++.h>
using namespace std;
#define ll int
#define mod 1000000007
#define INF 10000000000000  //10e13
#define ff first
#define ss second
#define PII pair<ll, ll>
#define PI acos(-1)
#define eps 0.000001

#define trace(x) cout<<#x<<": "<<x<<" "<<endl
#define trace2(x,y) cout<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl
#define trace3(x,y,z) cout<<#x<<":" <<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl
#define trace4(a,b,c,d) cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl

// idx = 1 for printing 1-indexed permutation
template<typename T>
void print_array(vector<T> &a, ll n = -1, ll idx = 0){
    if (n == -1)
        n = a.size();

    cout << "DEBUG: ";
    for (ll i = 0; i < n; i++)
        cout << a[i]+idx << " ";
    cout << endl;
}
void print_array(vector<PII> &a, ll n = -1){
    if (n == -1)
        n = a.size();
    cout << "DEBUG: ";
    for (ll i = 0; i < n; i++)
        cout << "(" << a[i].ff << ", " << a[i].ss << "); ";
    cout << endl;
}

ll add(ll a, ll b){
    return (a+b)%mod;
}
ll mul(ll a, ll b){
    return (a*b)%mod;
}

ll power(ll a, ll p){
    if (p == 0)
        return 1;
    ll x = power(a, p/2);
    x = mul(x,x);
    if (p % 2)
        x = mul(a, x);
    return x;
}

ll inv_mod(ll a){
    return power(a, mod-2);
}

/*
#define N 1001
ll fact[N], invfact[N];

void initNCR() {
    fact[0] = 1;
    ll i;
    for (i = 1; i < N; i++) {
        fact[i] = mul(i, fact[i - 1]);
    }
    i--;
    invfact[i] = inv_mod(fact[i]);
    for (i--; i >= 0; i--) {
        invfact[i] = mul((i + 1), invfact[i + 1]);
    }
}

ll ncr(ll n, ll r) {
    if (r > n || n < 0 || r < 0)
        return 0;
    return mul(mul(fact[n], invfact[r]), invfact[n - r]);
}
*/

ll gcd(ll a, ll b){
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

ll egcd(ll a, ll b, ll &x, ll &y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a%b, x1, y1);
    x = y1;
    y = x1-y1*(a/b);
    return g;
}

ll lcm(ll a, ll b){
    return a*b/gcd(a, b);
}
/*
bool cmp(pair<ll, vector<ll>> A, pair<ll, vector<ll>> B){
    return A.ff < B.ff;
}
*/

vector<ll> parent;
void make_set(ll v) {
    parent[v] = v;
}

ll find_set(ll v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

/*
void remove_el(idx){

}
void add_el(idx){

}
ll get_answer(){

};
*/

ll block_size;

struct Query {
    ll l, r, idx;
    Query(ll _l, ll _r, ll _i){
        l = _l;
        r = _r;
        idx = _i;
    }

    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

bool freqs[1000001];    // occurence positive or negative
ll odds;

void change(ll ele){
    if (freqs[ele])
        odds--;
    else
        odds++;
    freqs[ele] = !freqs[ele];
}

void mo_s_algorithm(vector<Query> &queries, vector<bool> &answers, vector<ll> &a) {
    answers = vector<bool> (queries.size());
    sort(queries.begin(), queries.end());

    odds = 0;    // how many with odd occurences

    ll cur_l = 0;
    ll cur_r = -1;

    for (Query q : queries) {
        if ( (q.r - q.l + 1) % 2){
            answers[q.idx] = false;
            continue;
        }

        while (cur_l > q.l) {
            cur_l--;
            change(a[cur_l]);   // add
        }
        while (cur_r < q.r) {
            cur_r++;
            change(a[cur_r]);   // add
        }
        while (cur_l < q.l) {
            change(a[cur_l]);   // remove
            cur_l++;
        }
        while (cur_r > q.r) {
            change(a[cur_r]);   // remove
            cur_r--;
        }

        //trace3(q.l, q.r, odds);
        answers[q.idx] = (odds == 0) ? true : false;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

    ll t;
    cin >> t;

    vector<bool> ans;

    while(t--){
        ll n, q, x;
        cin >> n >> q;

        block_size = ((ll) sqrt(n)) + 1;    // so that block s
        vector<ll> a(n);

        for (ll i = 0; i < n; i++){
            cin >> x;
            a[i] = x;
            freqs[x] = false;   // resetting this node
        }

        vector<Query> queries;
        for (ll i = 0; i < q; i++){
            ll l, r;
            cin >> l >> r;
            l--; r--;   // 0 based
            queries.push_back(Query(l, r, i));
        }

        mo_s_algorithm(queries, ans, a);

        for (ll i = 0; i < q; i++){
            if (ans[i])
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }

    }
    return 0;
}
