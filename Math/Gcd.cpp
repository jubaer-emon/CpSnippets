// ll gcd (ll a, ll b) {
//     while (b) {
//         a %= b;
//         swap(a, b);
//     }
//     return a;
// }

// ax + by = gcd(a,b)
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
    return a /gcd(a, b) * b;
}

// vector<ll> phi;
// void phi_1_to_n(ll n) {
//     phi.assign(n + 1);
//     for (ll i = 0; i <= n; i++)
//         phi[i] = i;

//     for (ll i = 2; i <= n; i++) {
//         if (phi[i] == i) {
//             for (ll j = i; j <= n; j += i)
//                 phi[j] -= phi[j] / i;
//         }
//     }
// }