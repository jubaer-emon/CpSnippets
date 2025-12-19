///https://codeforces.com/contest/1542/problem/B

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define INF 10000000000000
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

     //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

    ll t;
    cin >> t;
    while (t--){
        ll n, a, b;
        cin >> n >> a >> b;
        if ((n-1) % b == 0)
            cout << "YES" << endl;
        else{
            ll x, y;
            ll g = egcd(a, b, x, y);
            cout << g << " " << x << " x " << y << endl;

            if (n % g != 0)
                cout << "NO" << endl;
            else{
                ll p = a/g;
                ll q = b/g;
                x *= n/g;
                y *= n/g;
                // x & y were found for g, it has to be for n

                // the general solution is a(x-kq) + b(y+kp) = n
                if (x > 0 && y > 0)
                    cout << "YES" << endl;
                else if (x > 0 && y < 0){
                    // have to turn y positive
                    y = -y;
                    ll k = y/p;
                    if (y % p)
                        k++;    // ceil taken
                    if (x >= k*q)
                        cout << "YES" << endl;
                    else
                        cout << "NO" << endl;
                }
                else {
                    // have to turn x positive
                    x = -x;
                    ll k = x/q;
                    if (x % q)
                        k++;

                    if (y >= k*p)
                        cout << "YES" << endl;
                    else
                        cout << "NO" << endl;

                    x = -x+q*k;
                    y = y-k*p;
                    cout << x << " x " << y << endl;
                }
                // both will not be negative since n is positive
            }
        }
    }
    return 0;
}
