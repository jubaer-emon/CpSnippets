///https://www.codechef.com/problems/MCO16404

#include <bits/stdc++.h>
#define ll int
#define M 1000000007
#define PII pair<ll, ll>
#define ff first
#define ss second
using namespace std;


class Vertex{
public:
    vector<ll> entries;    //keeps data of entries sorted...
    vector<ll> next;
    Vertex(ll k){
        //string_ends = 0;
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

    ///binary strings of length = 20
    void add(string s, ll idx){
        ll cur = 0;
        for (char ch : s){
            ll c = ch-'0';  // 0 or 1 (two paths)

            // no path => make path
            if (nodes[cur].next[c] == -1){
                nodes[cur].next[c] = nodes.size();
                nodes.push_back(Vertex(K));
            }
            // travel to next path (whether by making or existing)
            cur = nodes[cur].next[c];

            /// this node contains a path of THIS INDEX
            nodes[cur].entries.push_back(idx);
        }

        // end of string
        //if (nodes[cur].string_ends == 0)
        //    nodes[cur].string_ends = tim;
    }

    // we will try to build up the best string
    string query(string s, ll L, ll R){
        string cur_string = "";
        ll cur = 0;
        for (char ch : s){
            ll c = ch-'0';

            bool best_route = false;
            ll n_node = nodes[cur].next[c];
            if (n_node != -1){
                vector<ll>::iterator itr = lower_bound(nodes[n_node].entries.begin(), nodes[n_node].entries.end(), L);
                if (itr != nodes[n_node].entries.end() && *itr <= R){
                    best_route = true;
                }
            }

            // if we can't travel through best path, go the alternate path (it is guaranteed there is at least a path)
            if (!best_route)
                c = 1-c;

            // travel to next path (existing)
            cur_string.push_back(c + '0');
            cur = nodes[cur].next[c];
        }
        // end of string
        return cur_string;
    }

    void print_trie(ll u, ll c, ll t) {
        //spaces
        for (ll s = 0; s < t; s++)
            cout << "  ";

        cout << c << "-> ";
        for (ll z : nodes[u].entries){
            cout << z << " ";
        }
        cout << endl;
        for (ll i = 0; i < K; i++){
            if (nodes[u].next[i] != -1)
                print_trie(nodes[u].next[i], i, t+1);
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /// BINARY TRIE
    Trie t(2);

    const int no_bits = 3;

    ll n, q, x;
    cin >> n;
    string str;

    //build the trie with given numbers
    for (ll i = 1; i <= n; i++){
        cin >> x;
        str = bitset<no_bits>(x).to_string();
        t.add(str, i);
    }

    t.print_trie(0, -1, 0);

    cin >> q;
    ll l, r;
    while(q--){
        cin >> l >> r >> x;
        ll y = x;
        x = ~x;
        x &= (1 << no_bits) -1;  // invert first 20 bits only

        str = bitset<no_bits>(x).to_string();
        //cout << "to do: " << str << endl;
        str = t.query(str, l, r);
        ll z = (ll) bitset<no_bits>(str).to_ulong();
        cout << (y ^ z) << endl;
    }

    return 0;
}
