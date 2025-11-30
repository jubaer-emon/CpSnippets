vl primes;
map<ll, ll> primeMap;

void sieve(ll LIM = 100000){
    vector<bool> is_prime(LIM+1, true);

    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= LIM; i++) {
        if (is_prime[i]) {
            primeMap[i] = primes.size();
            primes.push_back(i);

            for (ll j = i * i; j <= LIM; j += i)
                is_prime[j] = false;
        }
    }
}

vvl to_primes(ll x){
    ll p = primes[0];
    ll i = 1;
    vvl V;
    while (x != 1 && p * p <= x){
        ll z = 0;
        while (x % p == 0)
        {
            z++;
            x/= p;
        }
        if (z > 0)
            V.push_back({i, z}); //just push index
        p = primes[++i];
    }
    if (x != 1)
        V.push_back({primeMap[x], 1});  // the remaining num itself is prime

    return V;
}

// Need divisors of all numbers 1..n
vector<vector<ll>> divs;
void find_divs(ll LIM = 100000){
    divs.assign(LIM+1, 0);
    for (ll i = 1; i <= LIM; i++)
        for (ll j = i; j <= LIM; j += i)
            divs[j].push_back(i);
}

// Need divisors of arbitrary numbers repeatedly
// vector<ll> spf;
// void precomputeSPF(ll n = 100000){
//     spf.assign(n+1, 0);
//     for (ll i = 2; i <= n; i++) spf[i] = i;
//     for (ll i = 2; i*i <= n; i++)
//         if (spf[i] == i)
//             for (ll j = i*i; j <= n; j += i)
//                 if (spf[j] == j) spf[j] = i;
// }

// vector<ll> get_divisors(ll x) {
//     vector<pair<ll,ll>> fac;
//     while (x > 1) {
//         ll p = spf[x], cnt = 0;
//         while (x % p == 0) x /= p, cnt++;
//         fac.push_back({p, cnt});
//     }

//     vector<ll> res = {1};
//     for (auto &pr : fac) {
//         ll p = pr.first, c = pr.second;
//         ll sz = res.size();
//         long long mult = 1;
//         for (ll i = 1; i <= c; i++) {
//             mult *= p;
//             for (ll j = 0; j < sz; j++)
//                 res.push_back(res[j] * mult);
//         }
//     }
//     return res;
// }