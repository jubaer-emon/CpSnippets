#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define PII pair<ll,ll>
#define ff first
#define ss second
#define INF 10e17

void print_array(vector<ll> &a){
    ll n = a.size();
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

struct cmp {
    bool operator() (const PII &a, const PII &b) const {
        return a.ss < b.ss;
    }
};

int main(){
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);

    ll x, z, n;
    cin >> z >> n;
    multiset<PII, cmp> S;
    multiset<ll, greater<ll>> L;
    S.insert({0, z});
    L.insert(z);
    for (ll i = 0; i < n; i++){
        cin >> x;
        multiset<PII>::iterator itr = S.lower_bound({x, x});

        PII p = *itr;
        S.erase(itr);
        S.insert({p.ff, x});
        S.insert({x, p.ss});
        L.erase(L.find(p.ss-p.ff));
        L.insert(x-p.ff);
        L.insert(p.ss-x);
        cout << *L.begin() << " ";
    }
    return 0;
}
