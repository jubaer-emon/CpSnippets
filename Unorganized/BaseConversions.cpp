//a+b = (a^b) + 2*(a&b)

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

template<typename T>
void print_array(vector<T> &a, ll n = -1){
    if (n == -1)
        n = a.size();

    cout << "DEBUG: ";
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
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


///BASE
ll k;

void Xor(vector<ll> &a, vector<ll> &b, vector<ll> &ret){
    ret = vector<ll>(max(a.size(), b.size()));
    for (ll i = 0; i < ret.size(); i++){
        if (i < a.size() && i < b.size())
            ret[i] = (a[i]+b[i])%k;
        else if (i < a.size())
            ret[i] = a[i];
        else
            ret[i] = b[i];
    }
}


void Unxor(vector<ll> &a, vector<ll> &b, vector<ll> &ret){
    ret = vector<ll>(max(a.size(), b.size()));
    for (ll i = 0; i < ret.size(); i++){
        if (i < a.size() && i < b.size())
            ret[i] = (a[i]+k-b[i])%k;
        else if (i < a.size())
            ret[i] = a[i];
        else
            ret[i] = k-b[i];
    }
}

void tobasek(ll n, vector<ll> &ret){
    ll p = 1;
    ll i = 0;
    while (p*k <= n){
        p*=k;
        i++;
    }
    ret = vector<ll>(i+1, 0);
    for (; i >= 0; i--){
        ret[i] = n/p;
        n %= p;
        p /= k;
    }
}

ll todecimal(vector<ll> &dig){
    ll n = 0;
    ll p = 1;
    for (ll i = 0; i < dig.size(); i++){
        n += dig[i]*p;
        p *= k;
    }
    return n;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

    ll t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n >> k;

        // all guesses
        vector<ll> xo;
        ll r;
        for (ll i = 0; i < n; i++){
            vector<ll> tmp;
            vector<ll> i_digs;
            tobasek(i, i_digs);
            Unxor(i_digs, xo, tmp);    // to guess i, we have turn off turned on bits
            cout << todecimal(tmp) << endl;
            cout.flush();
            cin >> r;
            if (r)
                break;

            vector<ll> xo2 = vector<ll>(xo);    //copy
            Xor(xo2, tmp, xo);  // xo ^= (tmp) // tmp = i^xo
        }

        cout << endl;
    }
    return 0;
}
