///https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/D

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define M 1000000007
#define INF 1000000000
#define ff first
#define ss second
#define PII pair<ll, ll>

void print_array(vector<ll> &a){
    ll n = a.size();
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

ll power(ll a, ll p){
    if (p == 0)
        return 1;
    ll x = power(a, p/2);
    x = (x*x) % M;
    if (p % 2)
        x = (a*x) % M;
    return x;
}

ll inv_mod(ll a){
    return power(a, M-2);
}

ll gcd(ll a, ll b){
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

struct node{
    node *nxt = nullptr;
    ll val;
    node(ll _v){
        val = _v;
    }
};
struct LI{
    node *head = nullptr, *tail = nullptr;
};

vector<LI*> p;

// b gonna own
void unionp(ll a, ll b){
    if (p[b]->head == nullptr)
        p[b]->head = p[a]->head;
    else
        p[b]->tail->nxt = p[a]->head;

    p[b]->tail = p[a]->tail;
    p[a]->head = nullptr;
    p[a]->tail = nullptr;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, q;
    cin >> n >> q;


    for (ll i = 0; i < n; i++){
        node *nd = new node(i);
        LI *l = new LI;
        l->head = nd;
        l->tail = nd;
        p.push_back(l);
    }

    ll a, b;
    for (ll i = 0; i < q; i++){
        cin >> a >> b;
        a--; b--;
        unionp(a, b);
    }

    vector<ll> ans(n);
    for (ll i = 0; i < n; i++){
        node *s = p[i]->head;
        while (s != nullptr){
            ans[s->val] = i+1;
            s = s->nxt;
        }
    }

    for (ll i = 0; i < n; i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}
