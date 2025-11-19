
using ud = uniform_int_distribution<ll>;
void gen_tree() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    ll n = ud(2,20)(rng);
    cout << n << "\n";

    vl perm(n); rep(i,0,n) perm[i] = i+1;
    shuffle(all(perm), rng);

    for (ll v=1; v<n; v++) {
        ll u = ud(0,v-1)(rng); // u=0 -> star, u=v-1 -> line, u=v/2 -> binary tree
        cout << perm[u] << " " << perm[v] << "\n";
    }
}

