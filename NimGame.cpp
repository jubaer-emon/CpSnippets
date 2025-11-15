///https://atcoder.jp/contests/abc368/tasks/abc368_f

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


vector<vector<ll>> divs;
void find_divs(ll LIM){
    // Ignoring n itself
    for (ll i = 1; i <= LIM; i++)
        for (ll j = 2*i; j <= LIM; j += i)
            divs[j].push_back(i);
}



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
    return a.ff + a.ss < b.ff + b.ss;   // asc
}



bool comp(ll a, ll b){
    return a < b;   // for binary search, return where it fails first
}




///ARRAY is 1-indexed
ll T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees

//update node u -> val
void update(ll p, ll u, ll val, ll L, ll R){
    if (L == R){
        T[p] = add(T[p], val);    // ADD
    }
    else{
        ll mid = (L+R)/2;
        //we are only updating 1 index... so just go the right direction
        if (u <= mid)
            update(p*2, u, val, L, mid);
        else
            update(p*2+1, u, val, mid +1, R);
        T[p] = add(T[p*2], T[p*2 + 1]);
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    //this_thread::sleep_for(chrono::seconds(1));

    const ll maxN = 100000;

    ll t;
    //cin >> t;
    t = 1;
    divs = vector<vector<ll>>(maxN+1);
    find_divs(maxN);
    while (t--){

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
        cout << endl;
    }
    return 0;
}
