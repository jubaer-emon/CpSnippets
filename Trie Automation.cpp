#include <bits/stdc++.h>
#define ll long long
#define M 1000000007
#define PII pair<ll, ll>
#define ff first
#define ss second
using namespace std;


class Vertex{
public:
    vector<ll> string_ends; // we will store which strings end
    vector<ll> next;
    ll p;
    char pch;   //edge we took to get here
    ll suffix_link, exit_link;
    vector<ll> go;
    Vertex(ll k, ll pp, char c){
        p = pp;
        pch = c;
        suffix_link = -1;
        exit_link = -1;
        next.resize(k, -1);
        go.resize(k, -1);
    }
};

class Trie{
public:
    ll K;    // K=26 characters in Alphabet
    vector<Vertex> nodes;
    Trie (ll k){
        K = k;
        nodes.push_back(Vertex(K, -1, '#'));
        nodes[0].suffix_link = 0;
    }


    /// THE patterns will be used to build up the trie
    void add(string s, ll idx){
        ll cur = 0;
        for (char ch : s){
            ll c = ch-'a';

            // no path => make path
            if (nodes[cur].next[c] == -1){
                nodes[cur].next[c] = nodes.size();
                nodes.push_back(Vertex(K, cur, ch));
            }
            // travel to next path (whether by making or existing)
            cur = nodes[cur].next[c];
        }
        // end of string (if we only wanted to know if any string ends here
        // we would have kept a boolean like nodes[cur].isWord = true
        nodes[cur].string_ends.push_back(idx);
    }

    // look how many times a string exist
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
        return nodes[cur].string_ends.size();
    }

    // run full automation that will build up suffix suffix_links and failure paths (go)
    void build_automation(){
        for (ll i = 0; i < nodes.size(); i++){
            //cout << i << endl;
            for (ll j = 0; j < K; j++){

                go(i, j+'a');
            }
        }
    }

    // find all instances of patterns in the string
    void run_automation(string s, vector<ll> &occurs){
        ll cur = 0;
        //cout << cur << " ";
        for (char ch : s){
            ll c = ch-'a';
            cur = nodes[cur].go[c];

            for (ll v : nodes[cur].string_ends)
                occurs[v]++;

            ll e = nodes[cur].exit_link;
            while (e != -1){
                for (ll v : nodes[e].string_ends)
                    occurs[v]++;
                e = nodes[e].exit_link;
            }

            /// prints the order of state visit
            //cout << cur << " ";
        }
        //cout << endl;
    }

    /// also calculates exit links
    ll get_suffix_link(ll v){
        if (nodes[v].suffix_link == -1){

            //root node or parent is root
            if (v == 0  || nodes[v].p == 0){
                nodes[v].suffix_link = 0;
                nodes[v].exit_link = -1;
            }
            else{
                nodes[v].suffix_link = go(get_suffix_link(nodes[v].p), nodes[v].pch);

                //now the exit link
                ll s = nodes[v].suffix_link;
                while (s != 0)
                {
                    if (nodes[s].string_ends.size() > 0){
                        nodes[v].exit_link = s;
                        break;
                    }
                    s = get_suffix_link(s);
                }
            }
        }
        return nodes[v].suffix_link;
    }

    ll go(ll v, char ch){
        ll c = ch-'a';


        if (nodes[v].go[c] == -1){
            //original edge exist
            if (nodes[v].next[c] != -1)
                nodes[v].go[c] = nodes[v].next[c];
            else{
                // if root then itself or thru failure suffix_link (suffix)
                nodes[v].go[c] = (v == 0) ? 0 : go(get_suffix_link(v), ch);
            }
        }
        return nodes[v].go[c];
    }


    void print_trie(ll u, ll t) {
        //spaces
        for (ll s = 0; s < t; s++)
            cout << "  ";

        // with suffix link & exit link
        cout << u << "-> " << nodes[u].pch << " s=" << nodes[u].suffix_link << " e=" << nodes[u].exit_link << " (";
        //cout << u << "-> " << nodes[u].pch << " (";
        for (ll z : nodes[u].string_ends){
            cout << z << " ";
        }
        cout << ")" <<endl;
        for (ll i = 0; i < K; i++){
            if (nodes[u].next[i] != -1)
                print_trie(nodes[u].next[i], t+1);
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie t(26);

    string text;
    cin >> text;

    ll n;
    cin >> n;

    vector<string> patterns(n);


    for (ll i = 0; i < n; i++){
        cin >> patterns[i];
        t.add(patterns[i], i);
    }


    t.build_automation();
    t.print_trie(0, 0);

    vector<ll> occurs(n, 0);   // which pattern appears how many times
    t.run_automation(text, occurs);

    for (ll i = 0; i < n; i++){
        cout << occurs[i] << endl;
    }

    return 0;
}
