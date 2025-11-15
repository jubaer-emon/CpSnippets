///https://codeforces.com/contest/1538/problem/D

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define INF 10000000000000  //10e13
#define ff first
#define ss second
#define PII pair<ll, ll>
#define PI acos(-1)
#define eps 0.000001

void print_array(vector<ll> &a, ll n = -1){
    if (n == -1)
        n = a.size();
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

ll add(ll a, ll b){
    return (a+b)%M;
}
ll mul(ll a, ll b){
    return (a*b)%M;
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
    return power(a, M-2);
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

bool cmp(pair<ll, vector<ll>> A, pair<ll, vector<ll>> B){
    return A.ff < B.ff;
}

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


vector<ll> primes;
void sieve(){
    ll LIM = 32000;
    vector<bool> is_prime(LIM, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= LIM; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= LIM; j += i)
                is_prime[j] = false;
        }
    }
}

ll no_primes(ll x){
    ll cnt = 0;
    ll p = primes[0];
    ll i = 0;
    while (x != 1 && p * p <= x){
        while (x % p == 0)
        {
            cnt++;
            x/= p;
        }
        p = primes[++i];
    }
    if (x != 1)
        cnt++;  // the remaining num itself is prime
    return cnt;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);
    sieve();

    ll t;
    cin >> t;
    while (t--){
        ll a, b, k;
        cin >> a >> b >> k;
        if (k == 1){
            if (a == b)
                cout << "NO" << endl;
            else if (a % b == 0 || b % a == 0)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            continue;
        }

        ll g = gcd(a, b);
        ll x = a/g;
        ll y = b/g;
        ll s = no_primes(x) + no_primes(y) + 2*no_primes(g);
        if (s >= k)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}
