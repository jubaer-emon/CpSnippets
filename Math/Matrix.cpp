using mat = vvl; // or al<al<n>,m>

mat operator*(mat& a, mat& b) {
    ll m=sz(a), n=sz(a[0]), p=sz(b[0]);
    mat res(m,vl(p));
    rep(i,0,m) rep(j,0,p) rep(k,0,n) 
        res[i][j] += a[i][k] * b[k][j];
    return res;
}

mat pwr(mat& a, ll p) {
    mat res(sz(a),vl(sz(a)));
    rep(i,0,sz(a)) res[i][i] = 1;
    while (p>0) {
        if (p&1) res = res * a;
        a = a*a;
        p >>= 1;
    }
    return res;
}
