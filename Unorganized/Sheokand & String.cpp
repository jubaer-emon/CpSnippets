#include <bits/stdc++.h>
#define ll int
#define M 1000000007
#define PII pair<ll, ll>
#define ff first
#define ss second
using namespace std;


class Vertex{
public:
    ll string_ends, tim;    //string_ends will keep the earliest data of end of string

    vector<ll> next;
    Vertex(ll k, ll t){
        string_ends = 0;
        tim = t;
        next.resize(k, -1);
    }
};

class Trie{
public:
    ll K;    // K=26 characters in Alphabet
    ll tim;

    vector<Vertex> nodes;
    Trie (ll k){
        K = k;
        tim = 1;    //next string will create nodes of tim = 1
        nodes.push_back(Vertex(K, 0));
    }

    void add(string s){
        ll cur = 0;
        for (char ch : s){
            ll c = ch-'a';

            // no path => make path
            if (nodes[cur].next[c] == -1){
                nodes[cur].next[c] = nodes.size();
                nodes.push_back(Vertex(K, tim));
            }
            // travel to next path (whether by making or existing)
            cur = nodes[cur].next[c];
        }

        // end of string
        if (nodes[cur].string_ends == 0)
            nodes[cur].string_ends = tim;
        tim++;
    }

    // look for the
    string look(string s, ll r){
        ll cur = 0;
        string cur_string = "";

        for (char ch : s){
            ll c = ch-'a';

            // no path or path is newer than given r... cant extend longest prefix
            ll n_node = nodes[cur].next[c];
            if (n_node == -1 || nodes[n_node].tim > r){

                // try to find a valid string (which ended & belong in first r strings)
                while (nodes[cur].string_ends == 0 || nodes[cur].string_ends > r){
                    // try to find smallest character that we can travel through
                    ll i;
                    for (i = 0; i < K; i++){
                        //found a path through i
                        ll n_node = nodes[cur].next[i];
                        if (n_node != -1 && nodes[n_node].tim <= r)
                            break;
                    }

                    cur = nodes[cur].next[i];
                    cur_string.push_back(i+'a');
                }
                return cur_string;
            }

            // travel to next path (existing)
            cur = nodes[cur].next[c];
            cur_string.push_back(ch);
        }


        // found the whole string but not return it immediately
        // try to find a valid string (which ended & belong in first r strings)
        while (nodes[cur].string_ends == 0 || nodes[cur].string_ends > r){
            // try to find smallest character that we can travel through
            ll i;
            for (i = 0; i < K; i++){
                //found a path through i
                ll n_node = nodes[cur].next[i];
                if (n_node != -1 && nodes[n_node].tim <= r)
                    break;
            }

            cur = nodes[cur].next[i];
            cur_string.push_back(i+'a');
        }
        return cur_string;
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie t(26);

    ll n, q, r;
    cin >> n;
    string str;
    //build the trie with given strings
    for (ll i = 0; i < n; i++){
        cin >> str;
        t.add(str);
    }

    cin >> q;
    while(q--){
        cin >> r >> str;
        cout << t.look(str, r) << endl;
    }

    return 0;
}
