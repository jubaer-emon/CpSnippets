ll fact[MAXN];

ll nCk(ll n, ll k){
    return ((fact[n] * inv(fact[k], MOD) % MOD) * inv(fact[n-k], MOD)) % MOD;
}

fact[0] = 1;
f(i,1,MAXN) fact[i] = i * fact[i-1] % MOD;