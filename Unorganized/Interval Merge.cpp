///https://codeforces.com/contest/2020/problem/D

/* XOR PROPERTIES
    a|b = a^b + a&b
    a^(a&b) = (a|b)^b (b turned off but a on gives on)
    b^(a&b) = (a|b)^a (...)
    (a&b)|(a|b) = a|b

    a+b = a|b + a&b
    a+b = (a^b) + 2*(a&b)

    a-b = (a^(a&b))-((a|b)^a)
    a-b = ((a|b)^b)-((a|b)^a)
    a-b = (a^(a&b))-(b^(a&b))
    a-b = ((a|b)^b)-(b^(a&b))
/*

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
#define ll long long
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

bool cmp(pair<ll, vector<ll>> A, pair<ll, vector<ll>> B){
    return A.ff < B.ff;
}

vector<ll> parent;
vector<ll> sizes;
void make_set(ll v) {
    parent[v] = v;
    sizes[v] = 1;
}

ll find_set(ll v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b){
        if (sizes[a] < sizes[b])
            swap(a, b);
        parent[b] = a;
        sizes[a] += sizes[b];
    }
}

vector<PII> segs[11][11];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

    ll t;
    cin >> t;

    while(t--){
        ll n, m;
        cin >> n >> m;
        for (ll i = 0; i < 11; i++)
            for (ll j = 0; j < 11; j++)
                segs[i][j] = vector<PII>();

        for (ll i = 0; i < m; i++){
            ll a, d, k;
            cin >> a >> d >> k;
            segs[d][a%d].push_back({a, a+d*k});
        }

        vector<pair<ll, PII>> act_segs;

        // merge segs
        for (ll i = 0; i < 11; i++){
            for (ll j = 0; j < 11 ; j++){
                vector<PII> cur_segs = segs[i][j];
                if (!cur_segs.empty()){
                    sort(cur_segs.begin(), cur_segs.end());
                    for (ll k = 1; k < cur_segs.size(); k++){
                        // check end of last and start of this
                        // if overlap, make this the merged seg, not push yet
                        if (cur_segs[k-1].ss >= cur_segs[k].ff)
                            cur_segs[k] = {cur_segs[k-1].ff, max(cur_segs[k-1].ss, cur_segs[k].ss)};
                        else{
                            act_segs.push_back({i, cur_segs[k-1]});
                        }
                    }
                    act_segs.push_back({i, cur_segs.back()});   // last element
                }
            }
        }

        parent = vector<ll>(n+1);
        sizes = vector<ll>(n+1);
        for (ll i = 1; i <= n; i++)
            make_set(i);

        // work on merged segs (max. of about 100 segs)
        for (ll i = 0; i < act_segs.size(); i++){
            pair<ll, PII> pt = act_segs[i];
            ll dd = pt.ff;
            ll st = pt.ss.ff, ed = pt.ss.ss;
            for (ll j = st; j <= ed; j+= dd){
                union_sets(st, j);
            }
        }

        map<ll, bool> heads; // count how many different heads/ comps
        for (ll i = 1; i <= n; i++){
            ll h = find_set(i);
            if (heads.find(h) == heads.end())
                heads[h] = true;
        }
        cout << heads.size() << endl;
    }
    return 0;
}
