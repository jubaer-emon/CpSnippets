#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifndef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

using ll = long long;
using dl = double;
using pl = pair<ll,ll>;
using vl = vector<ll>;
using v2 = vector<vl>;
using v3 = vector<v2>;

#define f(i,s,e) for(long long int i=s;i<e;i++)
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const dl EPS = 1e-9;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tcs = 1; cin >> tcs;
    for (int tc = 1; tc <= tcs; tc++) {
        dbg(tc);
        
        $1
        
        // cout << "Case " << tc << ": ";
        
        cout << '\n';
    }
    return 0;
}