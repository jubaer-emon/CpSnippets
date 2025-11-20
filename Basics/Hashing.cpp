
struct chash {
    const ll random=(ll)(make_unique<char>().get())
        ^ chrono::high_resolution_clock::now().time_since_epoch().count();
    static unsigned ll splitmix64(unsigned ll x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    ll operator()(ll x) const {
        return splitmix64(x+random);
    }
    ll operator()(pl x) const {
        unsigned ll num=(x.first^(x.second>>1));
        return splitmix64(num+random);
    }
    //for vector as key similar can be done for lower collision
    ll operator()(string s) const {
        const ll p = 31;  
        //for only lowercase p=31,for lowercase+uppercase p=53
        ll hash_value = 0;
        ll p_pow = 1;
        for (char c : s) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % MOD;
            p_pow = (p_pow * p) % MOD;
        }
        return hash_value;
    }
};

