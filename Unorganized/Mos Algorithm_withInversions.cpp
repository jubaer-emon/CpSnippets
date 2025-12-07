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
#define dl double long
#define mod 1000000007
#define INF 1000000000000000  //10e15
#define inf9 1000000000 //10e9
#define ff first
#define ss second

#define pii pair<int, int>
#define PII pair<ll, ll>
#define vi vector<int>
#define VI vector<ll>
#define vii vector<pii>
#define VII vector<PII>
#define all(x) x.begin(), x.end()

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

void print_stack(stack<ll> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << a.top() << " ";
        a.pop();
    }
    cout << endl;
}
void print_stack(stack<PII> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << "(" << a.top().ff << ", " << a.top().ss << "); ";
        a.pop();
    }
    cout << endl;
}

void print_queue(queue<ll> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << a.front() << " ";
        a.pop();
    }
    cout << endl;
}
void print_queue(queue<PII> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << "(" << a.front().ff << ", " << a.front().ss << "); ";
        a.pop();
    }
    cout << endl;
}


void debug(string s){
    cout << "DEBUG: " << s << endl;
}

void debug(char ch){
    cout << "DEBUG: " << ch << endl;
}

void debug(PII p){
    cout << "DEBUG: " << "(" << p.ff << ", " << p.ss << ")" << endl;
}

ll add(ll a, ll b, ll m = -1){
    if (m == -1)
        m = mod;

    return (a+b)%m;
}
ll mul(ll a, ll b, ll m = -1){
    if (m == -1)
        m = mod;
    return (a*b)%m;
}

ll power(ll a, ll p, ll m = -1){
    if (m == -1)
        m = mod;
    if (p == 0)
        return 1;
    ll x = power(a, p/2);
    x = mul(x,x);
    if (p % 2)
        x = mul(a, x);
    return x;
}

ll inv_mod(ll a, ll m = -1){
    if (m == -1)
        m = mod;
    return power(a, m-2);
}


#define N 200001
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

void to_bin(ll x){
    cout << "DEBUG: " << bitset<32>(x).to_string() << endl;
}
struct cmpXY{
    bool operator()(const PII& a, const PII& b) const {
        if (a.ff != b.ff)
            return a.ff < b.ff;
        return a.ss < b.ss;
    }
};

struct cmpX{
    bool operator()(const PII& a, const PII& b) const {
        if (a.ff != b.ff)
            return a.ff > b.ff; // descending
        return a.ss > b.ss;
    }
};

struct cmpY{
    bool operator()(const PII& a, const PII& b) const {
        if (a.ss != b.ss)
            return a.ss > b.ss; // descending
        return a.ff > b.ff;
    }
};


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

vector<ll> primes;
vector<vector<ll>> prime_divs;
void sieve(){
    ll LIM = 1000;
    vector<bool> is_prime(LIM+1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= LIM; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i; j <= LIM*LIM; j += i){
                if (j <= LIM)
                    is_prime[j] = false;
                prime_divs[j].push_back(i);
            }
        }
    }
}

/*
vector<vector<ll>> divs;
void find_divs(ll LIM){
    for (ll i = 1; i <= LIM; i++)
        for (ll j = i; j <= LIM; j += i)
            divs[j].push_back(j);
}
*/


ll no_divs(ll n){
    ll cnt = 1;
    ll x = n;
    for (ll i = 0; i < prime_divs[n].size(); i++){
        ll p = prime_divs[n][i];
        ll j = 0;
        while (x % p == 0){
            x /= p;
            j++;
        }
        cnt *= (j+1);
    }
    if (x > 1)
        cnt *= 2;

    return cnt;
}

bool cmp(const PII& a, const PII& b) {
    return a.ss > b.ss;   // desc
}


vector<ll> T[10000001];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees
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

ll inv_cnt;
ll n;
vector<ll> a;

void ad(ll l, ll r, ll i, bool rt){
    ll q;
    q = query(1, l, r, 1, n, a[i]);
    if (rt)
        q = (r-l)-q;
    inv_cnt += q;
}

void remv(ll l, ll r, ll i, bool rt){
    ll q;
    q = query(1, l, r, 1, n, a[i]);
    if (rt)
        q = (r-l)-q;
}

void mo_s_algorithm(vector<Query> &queries, vector<bool> &answers, vector<ll> &a) {
    answers = vector<bool> (queries.size());
    sort(queries.begin(), queries.end());

    ll cur_l = 1;
    ll cur_r = 0;

    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            ad(cur_l, cur_r, cur_l, false);   // add
        }
        while (cur_r < q.r) {
            cur_r++;
            ad(cur_l, cur_r, cur_r, true);   // add
        }
        while (cur_l < q.l) {
            remv(cur_l, cur_r, cur_l, false);   // remove
            cur_l++;
        }
        while (cur_r > q.r) {
            remv(cur_l, cur_r, cur_r, true);   // remove
            cur_r--;
        }
        answers[q.idx] = (inv_cnt == 0) ? true : false;
    }
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    //this_thread::sleep_for(chrono::seconds(1));

    ll t;
    cin >> t;
    //t = 1;
    vector<bool> ans;

    while (t--){
        ll q, x;
        cin >> n >> q;

        block_size = ((ll) sqrt(n)) + 2;    // so that block s
        a = vector<ll>(n+1);

        inv_cnt = 0;

        for (ll i = 1; i <= n; i++)
            cin >> a[i];

        mergesort(a, 1, 1, n);  //build Segment Tree(a);


        vector<Query> queries;
        for (ll i = 0; i < q; i++){
            ll l, r;
            cin >> l >> r;
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
