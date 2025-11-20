
using ud = uniform_int_distribution<ll>;
void gen_testcase() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    ll tcs = ud(1,10)(rng); cout << tcs << "\n";
    rep(tc,0,tcs) {
        ll n = ud(1,100)(rng);
        cout << n << "\n";

        rep(i,0,n) cout << ud(1,1000)(rng) << " ";
        cout << "\n";
    }
    cout << "\n";
}

