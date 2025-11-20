
ll f(ll x) {
    return ;
}

// f(i) is a boolean function such that f(0) <= ... <= f(n-1)
ll binary_search(ll l, ll r) {
    while (r - l > 1) {
        ll m = (l + r) / 2;
        if (f(m)) {
            r = m; // 0 = f(l) < f(m) = 1
        } else {
            l = m; // 0 = f(m) < f(r) = 1
        }
    }
    return r; //l -> last zero, r -> first one
}

