#include <bits/stdc++.h>
#define ll long long
#define M 1000000007
#define PII pair<ll, ll>
#define ff first
#define ss second
using namespace std;

string text;
vector<ll> dp;

class Vertex{
public:
    bool string_ends;
    vector<ll> next;
    Vertex(ll k){
        string_ends = false;
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

    void add(string s){
        ll cur = 0;
        for (char ch : s){
            ll c = ch-'a';

            // no path => make path
            if (nodes[cur].next[c] == -1){
                nodes[cur].next[c] = nodes.size();
                nodes.push_back(Vertex(K));
            }
            // travel to next path (whether by making or existing)
            cur = nodes[cur].next[c];
        }
        // end of string (if we only wanted to know if any string ends here
        // we would have kept a boolean like nodes[cur].isWord = true
        nodes[cur].string_ends = true;
    }

    // look how many times a string exist
    /*
    ll look(string s){
        ll cur = 0;
        for (char ch : s){
            ll c = ch-'a';

            // no path => exit
            if (nodes[cur].next[c] == -1)
                return 0;

            // travel to next path (existing)
            cur = nodes[cur].next[c];
        }
        // end of string
        return nodes[cur].string_ends;
    }
    */

    // look for from a position of text
    ll look_for(ll pos){
        ll cur = 0;
        ll ans = 0;
        for (ll i = pos; i < text.length(); i++){
            ll c = text[i]-'a';

            // no path => exit
            if (nodes[cur].next[c] == -1)
                return ans;



            // travel to next path (existing)
            cur = nodes[cur].next[c];

            if (nodes[cur].string_ends)
            {
                ans += dp[i+1];
                ans %= M;
            }
        }

        // end of string
        return ans;
    }

    void print_trie(ll u, char ch, ll t) {
        //spaces
        for (ll s = 0; s < t; s++)
            cout << "  ";

        // with suffix link & exit link
        cout << u << "-> " << ch << " (";

        cout << nodes[u].string_ends;
        /*
        for (ll z : nodes[u].string_ends){
            cout << z << " ";
        }
        */

        cout << ")" <<endl;
        for (ll i = 0; i < K; i++){
            if (nodes[u].next[i] != -1)
                print_trie(nodes[u].next[i], i+'a', t+1);
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie t(26);

    cin >> text;

    ll n, k;
    cin >> k;
    string str;
    for (ll i = 0; i < k; i++){
        cin >> str;
        t.add(str);
    }

    //t.print_trie(0, '#', 0);

    n = text.length();
    dp = vector<ll> (n+1, 0);
    dp[n] = 1;

    for (ll i = n-1; i >= 0; i--){
        dp[i] = t.look_for(i);
    }

    cout << dp[0] << endl;


    return 0;
}
