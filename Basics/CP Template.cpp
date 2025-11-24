#include <bits/stdc++.h>
using namespace std;

template<typename V, typename T = typename enable_if<!is_same<V, string>::value, typename V::value_type>::type> ostream& operator<<(ostream &os, const V &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename H, typename... T> void dbg_out(H h, T... t) { cerr << ' ' << h; dbg_out(t...); }
void dbg_out() { cerr << endl; }
#ifdef LOCAL
#define dbg(...) cerr << __LINE__ << ":" << #__VA_ARGS__, dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define rep(i,s,e) for(ll i=s; i<e; i++)
#define all(a) (a).begin(), (a).end()
#define sz(x) ((int)x.size())

using ll = long long;
using dl = double;
using vl = vector<ll>;
using l2 = array<ll,2>;
using vl2 = vector<l2>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
template<int SZ> using al = array<ll, SZ>;

const int MAXN = 1e5 + 5; // or 1e6 + 5
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const dl EPS = 1e-9;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    
    int tcs = 1; cin >> tcs;
    for (ll tc = 1; tc <= tcs; tc++) {
        dbg(tc);
        
        $1
        
        // cout << "Case " << tc << ": ";
        cout << '\n';
    }
    return 0;
}