///https://codeforces.com/contest/1957/problem/C

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define INF 1000000000
#define ff first
#define ss second
#define PII pair<ll, ll>

void print_array(vector<ll> &a){
    ll n = a.size();
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

ll power(ll a, ll p){
    if (p == 0)
        return 1;
    ll x = power(a, p/2);
    x = (x*x) % M;
    if (p % 2)
        x = (a*x) % M;
    return x;
}

ll inv_mod(ll a){
    return power(a, M-2);
}

ll fact_mods[300005];
ll inv_fact_mods[300005];

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll prod = 1;
    fact_mods[0] = 1;
    inv_fact_mods[0] = inv_mod(1);

    for (ll i = 1; i <= 300002; i++)
    {
        prod = (prod*i)%M;
        fact_mods[i] = prod;
        inv_fact_mods[i] = inv_mod(prod);
    }

    //cout << "DOne" << endl;

    ll t;
    cin >> t;

    while (t--){
        ll n, k;
        cin >> n >> k;
        ll r, c;
        while (k--){
            cin >> r >> c;
            if (r != c)
                n -=2;
            else
                n--;
        }

        ll ans = 0;
        ll n_fact = 1;
        if (n % 2 == 0){
            for (ll i = 0; i <= n; i+=2){
                ll x = (fact_mods[n-i]*inv_fact_mods[(n-i)/2]) % M;
                x = (x*fact_mods[n])%M;
                x = (x*inv_fact_mods[i])%M;
                x = (x*inv_fact_mods[n-i])%M;
                ans = (ans+x)%M;
            }
        }
        else{
            for (ll i = 1; i <= n; i+=2){
                ll x = (fact_mods[n-i]*inv_fact_mods[(n-i)/2]) % M;
                x = (x*fact_mods[n])%M;
                x = (x*inv_fact_mods[i])%M;
                x = (x*inv_fact_mods[n-i])%M;
                ans = (ans+x)%M;
            }
        }

        if (ans < 0)
            ans += M;
        cout << ans << endl;
    }
    return 0;
}
