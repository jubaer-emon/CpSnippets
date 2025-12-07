/// Codeforces XOR Construction

#include <bits/stdc++.h>
using namespace std;

#define ll int
#define PII pair<ll,ll>
#define ff first
#define ss second

class Vertex{
public:
    ll num;
    vector<ll> next;
    Vertex(ll k){
        num = -1;
        next.resize(k, -1);
    }
};

class Trie{
public:
    ll K;    // K=26 characters in Alphabet
    vector<Vertex> nodes;
    Trie (ll k){
        K = k;
        nodes.push_back(Vertex(K));
    }


    /// THE patterns will be used to build up the trie
    void add(ll n){
        ll cur = 0;

        for (ll i = 0; i < 32; i++){
            ll b = 0;

            if (n & (1 << (31-i)) )
                b = 1;

            // no path => make path
            if (nodes[cur].next[b] == -1){
                nodes[cur].next[b] = nodes.size();
                nodes.push_back(Vertex(K));
            }
            // travel to next path (whether by making or existing)
            cur = nodes[cur].next[b];
        }
        // end of string
        nodes[cur].num = n;
    }

    // look how many times a string exist
    ll look(ll n){
        ll cur = 0;
        for (ll i = 0; i < 32; i++){
            ll b = 0;
            if (n & (1 << (31-i)) )
                b = 1;

            // no path => exit
            if (nodes[cur].next[b] == -1)
                b = 1-b;    // inverse digit to ensure there's path

            // travel to next path (existing)
            cur = nodes[cur].next[b];
        }
        // end of string
        return nodes[cur].num;
    }
};

int main(){
    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> c(n+1, 0);
    Trie t(2);

    for (ll i = 1; i < n; i++){
        cin >> a[i];
        c[i] = c[i-1]^a[i];
        t.add(c[i]);
    }

    // try 0 to n-1 for b1
    for (ll i = 0; i < n; i++){
        // b1 = i
        // try to find maximum by TRYING TO build the XOR inverse of b1
        ll maxi = i ^ t.look(~i);
        if (maxi < n)
        {
            ll b = i;
            for (ll j = 1; j <= n; j++){
                cout << b << " ";
                b = i ^ c[j]; // b(j+1) = b(1) ^ c(j)
            }
            break;
        }
    }
    return 0;
}
