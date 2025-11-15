#include <bits/stdc++.h>
#define ll long long
#define M 1000000007
#define PII pair<ll, ll>
#define ff first
#define ss second
#define INF 100000000
using namespace std;


class Vertex{
public:
    vector<ll> string_ends; // we will store which strings end
    //vector<ll> next;
    ll p;
    char pch;   //edge we took to get here
    ll suffix_link, exit_link;
    vector<ll> go;
    Vertex(ll k, ll pp, char c){
        p = pp;
        pch = c;
        //suffix_link = -1;
        exit_link = -1;
        //next.resize(k, -1);
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
            if (nodes[cur].go[c] == -1){
                nodes[cur].go[c] = nodes.size();
                nodes.push_back(Vertex(K, cur, ch));
            }
            // travel to next path (whether by making or existing)
            cur = nodes[cur].go[c];
        }
        // end of string (if we only wanted to know if any string ends here
        // we would have kept a boolean like nodes[cur].isWord = true
        nodes[cur].string_ends.push_back(idx);
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
        return nodes[cur].string_ends.size();
    }
    */

    /// COMPARE WITH GO AND GET LINKS RECURSIVE METHODS TO GET THE UNDERSTADNING OF BFS
    // see CP-Algorithms for details
    // run full automation that will build up suffix suffix_links and failure paths (go)
    void build_automation(){
        queue<ll> verts;    // for BFS
        //we will first set up the base case

        nodes[0].suffix_link = 0;
        for (ll j = 0; j < K; j++){
            if (nodes[0].go[j] != -1){
                nodes[nodes[0].go[j]].suffix_link = 0;    // the suffix links of immediate nodes are 0
                verts.push(nodes[0].go[j]);
            }
            else{
                nodes[0].go[j] = 0;   //to root itself
            }
        }
        /// root and connected to roots nodes exit links are -1 (no proper suffix that leads to word)
        //cout << nodes.size() << endl;

        while (!verts.empty()){
            // take the top node
            ll v = verts.front();
            verts.pop();

            // see for each character
            for (ll j = 0; j < K; j++){
                ll u = nodes[v].suffix_link;

                // there is original path
                if (nodes[v].go[j] != -1){
                    ll w = nodes[v].go[j];
                    // suffix link of w is its parent's suffix's 'go' thru node with parent char
                    // parent of w is v ... suffix of v is u... parent char is j
                    // see the recursive implementation
                    nodes[w].suffix_link = nodes[u].go[j];    // the suffix links of immediate nodes are 0

                    // was to find the exit link by traversing thru suffix links..
                    // case work => either immediate suffix is the exit or the exit is the exit of suffix
                    if (nodes[nodes[w].suffix_link].string_ends.size() > 0)
                        nodes[w].exit_link = nodes[w].suffix_link;
                    else
                        nodes[w].exit_link = nodes[nodes[w].suffix_link].exit_link;

                    verts.push(nodes[v].go[j]);
                }
                else{
                    nodes[v].go[j] = nodes[u].go[j];   //no original route => thru the suffix link's route
                }
            }
        }

        /*

        for (ll i = 0; i < nodes.size(); i++){
            //cout << i << endl;
            for (ll j = 0; j < K; j++){

                go(i, j+'a');
            }
        }
        */
    }

    // find all instances of patterns in the string
    // marked is the earliest instance of visit of node
    void run_automation(string s, vector<ll> &marked){
        ll cur = 0;
        marked = vector<ll>((ll)nodes.size(), -1);
        //cout << cur << " ";

        // the position
        ll pos = 1;
        for (char ch : s){
            ll c = ch-'a';
            cur = nodes[cur].go[c];

            // mark the node
            if (marked[cur] == -1)
                marked[cur] = pos;

            // visit all suffixes as well
            ll e = nodes[cur].exit_link;
            while (e != -1){
                if (marked[e] == -1)
                    marked[e] = pos;    // mark
                e = nodes[e].exit_link;
            }

            pos++;
            /// prints the order of state visit
            //cout << cur << " ";
        }
        //cout << endl;
    }

    /*

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

    */


    void print_trie(ll u, ll t) {
        //spaces
        for (ll s = 0; s < t; s++)
            cout << "  ";

        // with suffix link & exit link
        //cout << u << "-> " << nodes[u].pch << " s=" << nodes[u].suffix_link << " e=" << nodes[u].exit_link << " (";
        cout << u << "-> " << nodes[u].pch << " (";
        for (ll z : nodes[u].string_ends){
            cout << z << " ";
        }
        cout << ")" <<endl;
        for (ll i = 0; i < K; i++){
            if (nodes[u].go[i] != -1)   // implement & use next if want to see with links (after build)
                print_trie(nodes[u].go[i], t+1);
        }
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

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

    // see the structure of trie, in this implementation woudn't work after building (if want to then add next array as well, along with go)
    //t.print_trie(0, 0);
    t.build_automation();
    vector<ll> marked;   // which node appears how many times
    t.run_automation(text, marked);

    ///WHERE IT ENDS
    vector<ll> firsts(n, -1);  // which string appears first where

    ll sz = t.nodes.size();
    //for each node
    for (ll u = 0; u < sz; u++)
        for (ll v : t.nodes[u].string_ends){
            if (firsts[v] == -1)
                firsts[v] = marked[u];
            else
                firsts[v] = min(firsts[v], marked[u]);
        }

//cout << "YO" << endl;

    for (ll i = 0; i < n; i++){
        if (firsts[i] == -1)
            cout << -1 << endl;
        else
            cout << firsts[i]-patterns[i].length()+1 << endl;
    }

    return 0;
}
