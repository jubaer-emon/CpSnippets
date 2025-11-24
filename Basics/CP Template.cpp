#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
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
using l2 = array<ll,2>;
using pl = pair<ll,ll>;
using vb = vector<bool>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vl2 = vector<l2>;
using vpl = vector<pl>;

const int MAX_N = 1e5 + 5; // or 1e6 + 5
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