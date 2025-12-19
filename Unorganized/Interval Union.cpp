///https://codeforces.com/problemset/problem/1626/C

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

template<typename T>
void print_array(vector<T> &a, ll n = -1){
    if (n == -1)
        n = a.size();
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}
void print_array(vector<PII> &a, ll n = -1){
    if (n == -1)
        n = a.size();
    for (ll i = 0; i < n; i++)
        cout << "(" << a[i].ff << ", " << a[i].ss << "); ";
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);
    sieve();

    ll t;
    cin >> t;
    while (t--){
        ll n;
        cin >> n;
        vector<ll> k(n);
        vector<ll> h(n);
        for (ll i = 0; i < n; i++)
            cin >> k[i];
        for (ll i = 0; i < n; i++)
            cin >> h[i];
        vector<PII> segs;   // ff is position, ss is type (start/ end)

        for (ll i = 0; i < n; i++){
            segs.push_back({k[i]-h[i], 1}); // start
            segs.push_back({k[i], 0});  //end (will be processed before start)
        }
        sort(segs.begin(), segs.end());

        //print_array(segs);
        //cout << "I: " <<  segs.size() << endl;

        vector<PII> intervals;  // actual intervals (after unions)
        ll bal = 0;
        ll last = -1;
        for (ll i = 0; i < segs.size(); i++){
            if (bal == 0 && segs[i].ss == 1)
                last = segs[i].ff;  //position of start
            if (bal == 1 && segs[i].ss == 0)
                intervals.push_back({last, segs[i].ff}); // interval found

            if (segs[i].ss == 1)    // start
                bal++;
            else
                bal--;
        }



        ll ans = 0;
        // interval size sum is answer
        for (ll i = 0; i < intervals.size(); i++){
            ll L = intervals[i].ss - intervals[i].ff;
            ans += L*(L+1)/2;
        }
        cout << ans << endl;
    }

    return 0;
}
