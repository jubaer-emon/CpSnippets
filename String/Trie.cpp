class Vertex{
public:
    ll string_ends;
    vector<ll> next;
    Vertex(ll k){
        string_ends = 0;
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
        nodes[cur].string_ends++;
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
        return nodes[cur].string_ends;
    }


    void print_trie(ll u, ll c, ll t) {
        //spaces
        for (ll s = 0; s < t; s++)
            cout << "  ";

        if (u != 0){
            cout << (char) (c+'a') << "-> ";
            cout << nodes[u].string_ends;

            /*
            for (ll z : nodes[u].entries){
                cout << z << " ";
            }
            */

            cout << endl;
        }
        for (ll i = 0; i < K; i++){
            if (nodes[u].next[i] != -1)
                print_trie(nodes[u].next[i], i, t+1);
        }
    }
};

/*
    ll n, q;
    cin >> n >> q;
    string str;
    for (ll i = 0; i < n; i++){
        cin >> str;
        sort(str.begin(), str.end());
        t.add(str);
    }

    t.print_trie(0, ' ', 0);
*/