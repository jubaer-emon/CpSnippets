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
#define vl vector<ll>
#define vii vector<pii>
#define vpll vector<PII>
#define all(x) x.begin(), x.end()

#define f(i,l,r) for(ll i=l; (i)<r; i++)

#define eps 0.0000001

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

ll add(ll a, ll b, ll m = mod){
    return (a+b)%m;
}
ll mul(ll a, ll b, ll m = mod){
    return (a*b)%m;
}

ll power(ll a, ll p, ll m = mod){
    if (p == 0)
        return 1;
    ll x = power(a, p/2);
    x = mul(x,x);
    if (p % 2)
        x = mul(a, x);
    return x;
}

ll inv_mod(ll a, ll m = mod){
    return power(a, m-2);
}


#define N 1000001
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

//vector<ll> primes;
//vector<vector<ll>> prime_divs;
vector<bool> is_prime;

void sieve(ll LIM){
    is_prime = vector<bool>(LIM, true);
    is_prime[0] = is_prime[1] = false;
    //prime_divs = vector<vector<ll>>(LIM);

    ll ilim = sqrt(LIM) + 2;
    for (int i = 2; i < ilim; i++) {
        if (is_prime[i]) {
            // primes.push_back(i);
            for (ll j = 2*i; j < LIM; j += i){
                is_prime[j] = false;
                // prime_divs[j].push_back(i);
            }
        }
    }
}


vector<vector<ll>> divs;
void find_divs(ll LIM){
    divs = vector<vector<ll>>(LIM);
    // Ignoring n itself
    ll ilim = sqrt(LIM+1);
    for (int i = 2; i < LIM; i++)
        for (int j = i; j < LIM; j += i)
            divs[j].push_back(i);
}


/*
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
*/

bool cmp(const PII& a, const PII& b) {
    return a.ff + a.ss < b.ff + b.ss;   // asc
}



bool comp(ll a, ll b){
    return a < b;   // for binary search, return where it fails first
}

/*
void prefix_function(string s, vector<ll> &pi) {
    ll n = s.length();
    pi = vector<ll>(n);
    for (ll i = 1; i < n; i++) {
        ll j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
}
*/

vector<ll> mu;

void mobius (int lim) {
    mu = vector<ll>(lim);
    vector<int> primes;
    vector<int> lp(lim, 0); // lowest prime factor
    mu[1] = 1;

    for (int i = 2; i < lim; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1; // prime → μ(p) = -1
        }

        for (int p : primes) {
            if (p > lp[i] || 1LL * p * i > lim) break;

            lp[p * i] = p;

            if (p == lp[i]) {
                // p divides i → p^2 divides p*i → μ = 0
                mu[p * i] = 0;
                break;
            } else {
                // square-free, one more prime factor → multiply by -1
                mu[p * i] = -mu[i];
            }
        }
    }
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    //this_thread::sleep_for(chrono::seconds(1));


    initNCR();
    sieve(N);
    find_divs(N);
    mobius(N);

    ll tc = 0, tt;
    cin >> tt;
    //t = 1;
    while (tc++ < tt){
        ll n, k;
        cin >> n >> k;

        set<ll> S;

        for (ll i = 0; i < divs[n].size(); i++){
            ll p = divs[n][i];
            if (!is_prime[p])
                continue;
            ll s = n/p;
            S.insert(s);
        }

        ll ans = 0;
        for (ll s: S){
            for (ll i = 0; i < divs[s].size(); i++) {
                ll d = divs[s][i];
                ans = add( ans, mul(ncr(d-1, k), mu[s / d]) );
            }
        }


        if (ans < 0)
            ans += mod;
        cout << ans << '\n';
    }
    return 0;
}
