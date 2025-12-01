
ll add(ll a, ll b, ll m = MOD){
    return (a+b)%m;
}
ll mul(ll a, ll b, ll m = MOD){
    return (a*b)%m;
}

ll power(ll a, ll p, ll m = MOD){
    if (p == 0)
        return 1;
    ll x = power(a, p/2, m);
    x = mul(x,x, m);
    if (p % 2)
        x = mul(a, x, m);
    return x;
}

ll inv_mod(ll a, ll m = MOD){
    return power(a, m-2);
}

