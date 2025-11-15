///https://codeforces.com/contest/1957/problem/D

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

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    ll t;
    cin >> t;

    while (t--){
        ll n;
        cin >> n;
        vector<ll> a(n);
        for (ll i = 0; i < n; i++)
            cin >> a[i];

        vector<vector<PII>> dp(31, vector<PII>(n, {0,0}));

        for (ll b = 30; b >= 0; b--){
            ll cnt = 0;
            for (ll i = 0; i < n; i++){
                if (a[i] & (1<<b)){
                    dp[b][i].ff = cnt;
                    cnt = i-cnt;
                }
                else{
                    cnt++;
                }
            }

            cnt = 0;
            for (ll i = n-1; i >=0; i--){
                if (a[i] & (1<<b)){
                    dp[b][i].ss = cnt;
                    cnt = n-1-i-cnt;
                }
                else{
                    cnt++;
                }
            }
        }

        ll ans = 0;
        for (ll i = 0; i < n; i++){
            // find MSD
            for (ll b = 30; b >= 0; b--){
                if (a[i] & (1<<b)){
                    PII x = dp[b][i];
                    ans += i-x.ff;
                    ans += n-1-i-x.ss;
                    ans += x.ff * (n-1-i-x.ss);
                    ans += (i-x.ff) * x.ss;
                    break;
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
