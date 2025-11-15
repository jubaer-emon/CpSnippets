#include <bits/stdc++.h>
#define ll long long
#define M 1000000007
#define INF 1000000000000000
#define PII pair<ll, ll>
using namespace std;

///ARRAY is 0-indexed

PII T[450]; // sqrt (2 * 10^5)
ll box_sz;

void build(vector<ll> &a, ll n){

    ll p = 0;

    ll cnt = 0;
    ll mini = INF;

    //what is the minimum in current box going from left to right
    for (ll i = 0; i < n; i++, cnt++){
        if (cnt == box_sz){
            T[p].first = mini;
            mini = INF;
            cnt = 0;
            if (i != n)
                p++;
        }
        mini = min(a[i] + cnt, mini);
    }
    T[p].first = mini;  //last box

    mini = INF; cnt = 0; p = 0;

    //what is the minimum in current box going from right to left
    for (ll i = 0; i < n; i++, cnt++){
        if (cnt == box_sz){
            T[p].second = mini;
            cnt = 0;
            p++;
            mini = INF;
        }
        mini = min(a[i] + box_sz - cnt - 1, mini);
    }
    T[p].second = mini;
}

void update(vector<ll> &a, ll u, ll val){
    a[u] = val;

    ll p = u / box_sz;
    ll mini = INF;
    ll cnt = 0;

    //what is the minimum in current box going from left to right
    for (ll i = 0, cnt = 0; i < box_sz; i++, cnt++)
        mini = min(a[i + p*box_sz] + cnt, mini);
    T[p].first = mini;

    mini = INF;
    //what is the minimum in current box going from right to left
    for (ll i = box_sz-1, cnt = 0; i >= 0; i--, cnt++)
        mini = min(a[i + p*box_sz] + cnt, mini);
    T[p].second = mini;
}

ll query(vector<ll> &a, ll u, ll n){
    ll mini = INF;
    ll p = u/ box_sz;
    ll L = p*box_sz;
    ll R = L + box_sz - 1;
    ll cnt;

    //option 1 (going right, in the box itself where b is)
    for (ll i = u, cnt = 0; i <= R; i++, cnt++){
        mini = min(a[i] + cnt, mini);
    }

    //option 2 (going left, in the box itself where b is)
    for (ll i = u, cnt = 0; i >= L; i--, cnt++){
        mini = min(a[i] + cnt, mini);
    }

    //option 3 (going left, not in current box)
    ll x = p-1;
    while (x >= 0){
        mini = min(u-((x+1)*box_sz)+1 + T[x].second, mini);
        x--;
    }
    //option 4 (going right)
    x = p+1;    //index
    while (x*box_sz < n){
        mini = min( (x * box_sz -1)-u+1 + T[x].first, mini);
        x++;
    }

    return mini;
}

int main(){

    freopen ("test_input.txt","r",stdin);
    freopen ("output.txt","w",stdout);

    ll n, q;
    cin >> n >> q;

    box_sz = sqrt(n)+1;
    ll N = box_sz * (n/box_sz) + 1;
    vector<ll> p(N);

    for(ll i = 0; i < n; i++)
        cin >> p[i];

    for (ll i = n+1; i < N; i++)
        p[i] = INF;

    build(p, n);  //build Segment Tree
//cout << box_sz << " x" << endl;
    ll op, u, v;
    ll d = 1;
    while(q--){
        cin >> op;
        if (op == 1){
            cin >> u >> v;
            u--;
            update(p, u, v);
        }
        else{

            cin >> u;
            u--;
            cout << query(p, u, n) << endl;


        }

    }
    return 0;
}
