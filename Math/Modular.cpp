#pragma region Modular Arithmetic

ll add(ll a, ll b, ll m = MOD){
    return (a+b)%m;
}

ll sub(ll a, ll b, ll m = MOD){
    return (a - b + m) % m;
}

ll pwr(ll a, ll p, ll mod=MOD) {
    a %= mod;
    ll res = 1;
    while (p > 0) {
        if (p & 1)
            res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

ll mul(ll a, ll b, ll m = MOD){
    return (a*b)%m;
}

ll inv(ll a, ll m = MOD){
    return pwr(a, m-2, m);
}

#pragma endregion Modular Arithmetic