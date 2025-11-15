/* XOR PROPERTIES
    a|b = a^b + a&b
    a^(a&b) = (a|b)^b (b turned off but a on gives on)
    b^(a&b) = (a|b)^a (...)
    (a&b)|(a|b) = a|b

    a+b = a|b + a&b
    a+b = (a^b) + 2*(a&b)

    a-b = (a^(a&b))-((a|b)^a)
    a-b = ((a|b)^b)-((a|b)^a)
    a-b = (a^(a&b))-(b^(a&b))
    a-b = ((a|b)^b)-(b^(a&b))
/*

/*
        //iterate through MAP:

        map<ll, vector<ll>> nums;
        for (auto const& ele: nums){
            vector<ll> V = ele.second;
        }


        // ORDERING

        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](ll i, ll j) {
            return b[i] < b[j]; // small b first
        });
*/


#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define dl double long
#define mod 1000000007
//#define INF 10000000000000  //10e13
#define ff first
#define ss second
#define PII pair<ll, ll>
#define PI acos(-1)
#define eps 0.000001

#define trace(x) cout<<#x<<": "<<x<<" "<<endl
#define trace2(x,y) cout<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl
#define trace3(x,y,z) cout<<#x<<":" <<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl
#define trace4(a,b,c,d) cout<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl

// idx = 1 for printing 1-indexed permutation
template<typename T>
void print_array(vector<T> &a, ll n = -1, ll idx = 0){
    if (n == -1)
        n = a.size();

    cout << "DEBUG: ";
    for (ll i = 0; i < n; i++)
        cout << a[i]+idx << " ";
    cout << endl;
}
void print_array(vector<PII> &a, ll n = -1){
    if (n == -1)
        n = a.size();
    cout << "DEBUG: ";
    for (ll i = 0; i < n; i++)
        cout << "(" << a[i].ff << ", " << a[i].ss << "); ";
    cout << endl;
}

void debug(string s){
    cout << "DEBUG: " << s << endl;
}

ll add(ll a, ll b){
    return (a+b)%mod;
}
ll mul(ll a, ll b){
    return (a*b)%mod;
}

ll power(ll a, ll p){
    if (p == 0)
        return 1;
    ll x = power(a, p/2);
    x = mul(x,x);
    if (p % 2)
        x = mul(a, x);
    return x;
}

ll inv_mod(ll a){
    return power(a, mod-2);
}

/*
#define N 1001
ll fact[N], invfact[N];

void initNCR() {
    fact[0] = 1;
    ll i;
    for (i = 1; i < N; i++) {
        fact[i] = mul(i, fact[i - 1]);
    }
    i--;
    invfact[i] = inv_mod(fact[i]);
    for (i--; i >= 0; i--) {
        invfact[i] = mul((i + 1), invfact[i + 1]);
    }
}

ll ncr(ll n, ll r) {
    if (r > n || n < 0 || r < 0)
        return 0;
    return mul(mul(fact[n], invfact[r]), invfact[n - r]);
}
*/

ll gcd(ll a, ll b){
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

ll egcd(ll a, ll b, ll &x, ll &y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = egcd(b, a%b, x1, y1);
    x = y1;
    y = x1-y1*(a/b);
    return g;
}

ll lcm(ll a, ll b){
    return a*b/gcd(a, b);
}

bool cmp(pair<ll, vector<ll>> A, pair<ll, vector<ll>> B){
    return A.ff < B.ff;
}

vector<ll> parent;
vector<ll> sizes;
void make_set(ll v) {
    parent[v] = v;
    sizes[v] = 1;
}

ll find_set(ll v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b){
        if (sizes[a] < sizes[b])
            swap(a, b);
        parent[b] = a;
        sizes[a] += sizes[b];
    }
}

bool customComparator(const pair<ll, PII>& a, const pair<ll, PII>& b) {
    return a.ff < b.ff;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("test_input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);
}

    /// DP
    /// LCS
    string a, b;
    cin >> a >> b;
    ll A = a.length();
    ll B = b.length();
    vector<vector<pair<ll, PII> >> dp(A+1, vector<pair<ll, PII>>(B+1, {0, {0, 0}})); // first lcs, second is last common point (for rebuild)
    for (ll i = 1; i <= A; i++){
        for (ll j = 1; j <= B; j++){
            if (a[i-1] == b[j-1]){
                dp[i][j] = {dp[i-1][j-1].ff + 1, {i, j}};
            }
            else{
                if (dp[i-1][j].ff > dp[i][j-1].ff)
                    dp[i][j] = dp[i-1][j];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
    }
    string lcs = "";
    PII pos = dp[A][B].ss;

    while (pos.ff != 0){
        lcs += (char) a[pos.ff-1];  //0-based

        pos.ff--;
        pos.ss--;
        pos = dp[pos.ff][pos.ss].ss;
    }

    reverse(lcs.begin(), lcs.end());
    cout << lcs << endl;


    /// DIGIT DP
    // Returns number of numbers between 0 and b inclusive, where no two adjacent digits are same

    ll digit_dp(string b){
        ll len = b.length();
        // Restriction in first digit
        ll F = b[0] - '0';  // FIRST DIGIT
        vector<vector<ll>> dp(20, vector<ll>(10, 0));

        if (len == 1)
            return F+1;

        ll lim = 9; // last digit limit to try in first place
        ll cnt = 10;    // from 0 to 9 = 10
        dp[0][0] = 1;
        for (ll i = 0; i <= 9; i++)
            dp[1][i] = 1;

        for (ll d = 2; d <= len; d++){

            // first digit 0
            for (ll j = 1; j <= 9; j++)
                dp[d][0] += dp[d-1][j];

            if (d == len)
                lim = F-1;

            for (ll i = 1; i <= lim; i++){

                for (ll j = 0; j <= 9; j++){
                    if (i == j)
                        continue;

                    dp[d][i] += dp[d-1][j];
                }
                cnt += dp[d][i];
            }


            if (d == len){

                //cout << cnt << endl;

                // limiting number placed
                // next number must be less than 2nd number
                // or equal, then again, the subsequent number must be less than 3rd number
                bool broken = false;
                for (ll e = 1; e < len; e++){
                    for (ll j = 0; j < b[e]-'0'; j++){
                        if (j != b[e-1]-'0')
                            dp[d][F] += dp[d-e][j];
                    }

                    if (b[e] == b[e-1]){
                        broken = true;
                        break;
                    }
                }
                if (!broken){
                    dp[d][F] += dp[0][0];   // +1
                }

                cnt += dp[d][F];
            }
        }
        return cnt;
    }

    ll x = digit_dp(to_string(b));

    /// Knapsack 1 (N <= 100, W <= 10^5, vi <= 10^9)
    cin >> n >> W;
    vector<ll> a(n+1), b(n+1);
    vector<ll> dp(W+1, 0);
    for (ll i = 1; i <= n; i++)
        cin >> a[i] >> b[i];    // a weight, b value

    for (ll i = 1; i <= n; i++)
        for (ll w = W; w >= 1; w--)
            if (w >= a[i])
                dp[w] = max(dp[w], dp[w-a[i]] + b[i]);
    cout << dp[W] << endl;

    /// Knapsack 2 (N <= 100, W <= 10^9, vi <= 10^3)
    ll maxV = n * 1000;
    vector<ll> a(n+1), b(n+1);
    vector<ll> dp(maxV+1, INF); // to make V, the minimum weight (using upto i)
    dp[0] = 0;
    for (ll i = 1; i <= n; i++)
        cin >> a[i] >> b[i];    // a weight, b value

    for (ll i = 1; i <= n; i++)
        for (ll v = maxV; v >= 1; v--)
            if (v >= b[i])
                dp[v] = min(dp[v], dp[v-b[i]] + a[i]);

    for (ll v = maxV; v >= 0; v--){
        if (dp[v] <= W){
            cout << v << endl;
            break;
        }
    }

    /// Elevator Rides (max. weight W, min. number number of rides)
    vector<PII> dp(1<<n);   // first is min. rides, second is min. weight
    dp[0] = {1, 0}; // First elevator
    for (ll i = 1; i < (1<<n); i++){
        dp[i] = {INF, INF};

        // j is person (the last person to be included in last ride)
        // try to find without j and consider including j in subset [j belongs to i]
        for (ll j = 0; j < n; j++){
            if (i & (1 << j)){
                // without j
                PII p = dp[i ^ (1 << j)];
                ll s = p.ff;
                ll W = p.ss;

                // needs new lift for "j"
                if (W + w[j] > x){
                    s++;
                    W = min(W, w[j]);
                }
                else
                    W += w[j];

                // less steps OR equal steps but less weight in last lift
                if ((s < dp[i].ff) || (s == dp[i].ff && W < dp[i].ss))
                    dp[i] = {s, W};
            }
        }
    }

    cout << dp[(1<<n)-1].ff << endl;


    /// Counting Tiles (SUBMASK DP) => ways to fill n x m with 1x2 / 2x1
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> dp(2, vector<ll> (1<<n, 0) );
    vector<bool> validmasks((1<<n)-1, false);

    ll lim = (1<<n)-1;
    // base case & valid masks
    for (ll i = 0; i < n; i++){
        for (ll s = 0; s <= lim; s++){
            // if 1s are in even segments then valid
            bool valid = true;
            ll c = 0;
            for (ll x = 0; x < n; x++){
                if (s & (1 << x))
                    c++;
                else{
                    if (c % 2){
                        valid = false;
                        break;
                    }
                    c = 0;
                }
            }
            if (c % 2)
                valid = false;

            if (valid){
                validmasks[s] = true;
                dp[0][~s & lim] = 1;  // horizontal tiles in those empty places, leaking into next column
            }
        }
    }

    for (ll j = 1; j < m; j++){
        for (ll s = 0; s <= lim; s++){
            // Column transition: dp[0][s] => dp[1][s]
            // for mask s, the previous column must have 0 where there's 1 (horizontal block used that leaks into next)
            // and in places where 0, it can be 1 or 0
            // So, subsets of ~s
            dp[1][s] = 0;
            ll x = ~s & lim;
            for (ll t = x; ; t=(t-1)&x){
                // t is covered from previous cell (horizontal block)
                // s is covered from this cell (horizontal block)
                if (validmasks[~(t|s) & lim])   // remaining cells can be covered with vertical blocks
                    dp[1][s] = (dp[1][s]+dp[0][t])%M;

                if (t == 0)
                    break;
            }
        }
        for (ll s = 0; s <= lim; s++)
            dp[0][s] = dp[1][s];
    }

    cout << dp[0][0] << endl;

    /// Projects
    struct node{
    ll st, ed, pt;
    node(){}
    node(ll s, ll e, ll p){
        st = s;
        ed = e;
        pt = p;
        }
    };

    vector<node> p(n);
    for (ll i = 0; i < n; i++)
        cin >> p[i].st >> p[i].ed >> p[i].pt;

    sort (p.begin(), p.end(), cmp_node);

    vector<ll> dp(n, 0);
    vector<ll> eds(n);
    for (ll i = 0; i < n; i++)
        eds[i] = p[i].ed;

    dp[0] = p[0].pt;
    for (ll i = 1; i < n ; i++){
        // two options
        // take this project and make better or use projects till before
        dp[i] = dp[i-1];
        ll idx = lower_bound(eds.begin(), eds.end(), p[i].st) - eds.begin() - 1;
        //cout << idx << endl;
        ll prev = 0;
        if (idx != -1)
            prev = dp[idx];

        ll used = p[i].pt + prev;
        if (used > dp[i])
            dp[i] = used;
    }

    cout << dp[n-1] << endl;


    /// LINKED LIST
    // https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/D
    // n tools in box. query => put all from s into t
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

    main(){
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
    }


    /// Mo's Algorithm (unique elements between l,r.. and if frequency odd => answer yes)
    /*
    void remove_el(idx){

    }
    void add_el(idx){

    }
    ll get_answer(){

    };
    */

    ll block_size;

    struct Query {
        ll l, r, idx;
        Query(ll _l, ll _r, ll _i){
            l = _l;
            r = _r;
            idx = _i;
        }

        bool operator<(Query other) const
        {
            return make_pair(l / block_size, r) <
                   make_pair(other.l / block_size, other.r);
        }
    };

    bool freqs[1000001];    // occurence positive or negative
    ll odds;

    void change(ll ele){
        if (freqs[ele])
            odds--;
        else
            odds++;
        freqs[ele] = !freqs[ele];
    }

    void mo_s_algorithm(vector<Query> &queries, vector<bool> &answers, vector<ll> &a) {
        answers = vector<bool> (queries.size());
        sort(queries.begin(), queries.end());

        odds = 0;    // how many with odd occurences

        ll cur_l = 0;
        ll cur_r = -1;

        for (Query q : queries) {
            if ( (q.r - q.l + 1) % 2){
                answers[q.idx] = false;
                continue;
            }

            while (cur_l > q.l) {
                cur_l--;
                change(a[cur_l]);   // add
            }
            while (cur_r < q.r) {
                cur_r++;
                change(a[cur_r]);   // add
            }
            while (cur_l < q.l) {
                change(a[cur_l]);   // remove
                cur_l++;
            }
            while (cur_r > q.r) {
                change(a[cur_r]);   // remove
                cur_r--;
            }
            answers[q.idx] = (odds == 0) ? true : false;
        }
    }

    main(){
        block_size = ((ll) sqrt(n)) + 1;    // so that block s
        vector<ll> a(n);

        for (ll i = 0; i < n; i++){
            cin >> x;
            a[i] = x;
            freqs[x] = false;   // resetting this node
        }

        vector<Query> queries;
        for (ll i = 0; i < q; i++){
            ll l, r;
            cin >> l >> r;
            l--; r--;   // 0 based
            queries.push_back(Query(l, r, i));
        }

        mo_s_algorithm(queries, ans, a);

        for (ll i = 0; i < q; i++){
            if (ans[i])
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
        }
    }


    /// TRIE
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

    main(){
        Trie t(26);
        ll n, q;
        cin >> n >> q;
        string str;
        for (ll i = 0; i < n; i++){
            cin >> str;
            sort(str.begin(), str.end());
            t.add(str);
        }

        t.print_trie(0, ' ', 0);

        /*
        while(q--){
            cin >> str;
            cout << t.look(str) << endl;
        }
        */
    }

    /// WITH BFS AUTOMATION
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
            //suffix_link = -1;
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
                if (nodes[cur].go[c] == -1){
                    nodes[cur].go[c] = nodes.size();
                    nodes[cur].next[c] = nodes.size();  // just storing, no real use except printing trie
                    nodes.push_back(Vertex(K, cur, ch));
                }
                // travel to next path (whether by making or existing)
                cur = nodes[cur].go[c];
            }
            // end of string (if we only wanted to know if any string ends here
            // we would have kept a boolean like nodes[cur].isWord = true
            nodes[cur].string_ends.push_back(idx);
        }

        /// COMPARE WITH GO AND GET LINKS RECURSIVE METHODS TO GET THE UNDERSTADNING OF BFS
        // see CP-Algorithms for details
        // run full automation that will build up suffix suffix_links and failure paths (go)
        void build_automation(){
            queue<ll> verts;    // for BFS
            //we will first set up the base case

            nodes[0].suffix_link = 0;
            for (ll j = 0; j < K; j++){
                ll next_node = nodes[0].go[j];
                if (next_node != -1){
                    nodes[next_node].suffix_link = 0;    // the suffix links of immediate nodes are 0
                    verts.push(next_node);
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
        }

        // find all instances of patterns in the string
        void run_automation(string s, vector<ll> &marked){
            ll cur = 0;
            marked = vector<ll>((ll)nodes.size());
            //cout << cur << " ";
            for (char ch : s){
                ll c = ch-'a';
                cur = nodes[cur].go[c];

                // increase the visit counter of this node
                marked[cur]++;

                // visit all suffixes as well
                ll e = nodes[cur].exit_link;
                while (e != -1){
                    marked[e]++;    // increase the visit counter of this node
                    e = nodes[e].exit_link;
                }

                /// prints the order of state visit
                //cout << cur << " ";
            }
            //cout << endl;
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
                if (nodes[u].next[i] != -1)   // implement & use next if want to see with links (after build)
                    print_trie(nodes[u].next[i], t+1);
            }
        }
    };


    main(){
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

        vector<ll> marked;   // which node appears how many times
        t.run_automation(text, marked);

        vector<ll> occurs(n, 0);  // which string appears how many times
        ll sz = t.nodes.size();
        //for each node
        for (ll u = 0; u < sz; u++)
            for (ll v : t.nodes[u].string_ends)
                occurs[v] += marked[u];

        for (ll i = 0; i < n; i++){
            cout << occurs[i] << endl;
        }
    }

    /// KMP
    void prefix_function(string s, vector<ll> &pi) {
        ll n = s.length();
        pi = vector<ll>(n);
        for (ll i = 1; i < n; i++) {
            ll j = pi[i-1];  ///we try to add up on previous best result...

            ///IF the previous prefix did not work (s[i] != s[j]), let us try with even shorter prefix!!!
            ///and to pick the next probable highest length 'j', we have to pick j = pi[j-1]... THINK!
            while (j > 0 && s[i] != s[j])
                j = pi[j-1];


            ///NOTICE, we add one to prefix value of previous position (we are trying to add one character
                                                                        ///and equal a 'prefix' to suffix)
            //abcabcabgf... at index 6('a').. pi[6] = pi[5] + 1 = 3... as, pi[5] = 2.. and [2] == [6] == c
            //maximum value prefix function can reach is array size(index) = (n-1) (example: 'aaaaaa')
            if (s[i] == s[j])
                j++;

            pi[i] = j;
        }
    }

    //p = pattern, t = text
    ///returns a list of occurence positions
    void sub_search(string p, string t, vector<ll> &occurs){
        vector<ll> pre;
        prefix_function(p+"#"+t, pre);

        ll k = p.length();
        ll n = k + t.length() + 1;
        for (ll i = k+1; i < n; i++){
            //cout << pre[i] << "a ";

            //i is the end index of occurence (*in the merged text*)
            if (pre[i] == k)
                occurs.push_back(i-2*k);    //pushes start index of occurences
        }
    }

    /// counts prefixes of s within s
    void count_prefixes(string s, vector<ll> &cnt){
        vector<ll> pi;
        // calculate the prefix array
        prefix_function(s, pi);

        ll n = s.length();

        cnt = vector<ll> (n + 1); // cnt[i] = prefix of i length

        // at position i, the prefix of length pi[i] ends, so count that
        for (ll i = 0; i < n; i++)
            cnt[pi[i]]++;
        // for all prefixes of length i,
        // the smaller prefix within that prefix needs to be counted as well
        // the smaller prefix = pi[i-1]  ==> i = length and i-1 = index
        for (ll i = n-1; i > 0; i--)
            cnt[pi[i-1]] += cnt[i];
        // original prefixes
        for (ll i = 0; i <= n; i++)
            cnt[i]++;
    }


    /// counts prefixes of s within t
    void count_prefixes_other(string s, string t, vector<ll> &cnt){
        string cat = s + "#" + t;

        ll n = s.length();
        ll L = cat.length();
        vector<ll> pi;
        // calculate the prefix array
        prefix_function(cat, pi);

        cnt = vector<ll>(n + 1); // cnt[i] = prefix of i length
        // at nth position is #... we have to count from n+1
        for (ll i = n+1; i < L; i++)
            cnt[pi[i]]++;
        for (ll i = n-1; i > 0; i--)
            cnt[pi[i-1]] += cnt[i];

        /*  no original prefixes
        for (ll i = 0; i <= n; i++)
            cnt[i]++;
        */
    }


    main(){
        string a, b;    //a is pattern
        cin >> a >> b;

        /// PREFIX COUNT OF S
        vector<ll> cnt;
        count_prefixes(a, cnt);
        cout << "PREFIX counts of " << a << endl;
        for (ll i = 1; i <= a.length(); i++){
            cout << cnt[i] << endl;
        }
        cout << endl;


        /// PREFIX COUNT OF S within T
        cnt.clear();
        count_prefixes_other(a, b, cnt);
        cout << "PREFIX counts of " << a << " in " << b << endl;
        for (ll i = 1; i <= a.length(); i++){
            cout << cnt[i] << endl;
        }
        cout << endl;


        /// POSITIONS of s within T
        vector<ll> pos;
        sub_search(a, b, pos);
        cout << pos.size() << endl;

        for (ll i = 0; i < pos.size(); i++){
            cout << pos[i] << " ";
        }
    }


    /// SEGMENT TREE
    ///ARRAY is 1-indexed
    ll T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees
    ll S[1000000];  // lazy

    // p is the node/segment
    void build(vector<ll> &a, ll p, ll L, ll R){
        //base case
        if (L == R)
            T[p] = a[L];
        else{
            //let us now divide... i.e: for [1, 4] -> [1,2] + [3,4] or [1,5] -> [1,2] + [3,4,5]
            ll mid = (L+R)/2;
            build(a, p*2, L, mid);
            build(a, p*2+1, mid+1, R);

            /// now combine from left and right.. this is the combine function part
            T[p] = MIN(T[p*2], T[p*2 + 1]);
        }
    }

    //update node u -> val
    void update(ll p, ll u, ll val, ll L, ll R){
        if (L == R){
            T[p] = val;
        }
        else{
            ll mid = (L+R)/2;
            //we are only updating 1 index... so just go the right direction
            if (u <= mid)
                update(p*2, u, val, L, mid);
            else
                update(p*2+1, u, val, mid +1, R);
            T[p] = MIN(T[p*2], T[p*2 + 1]);
        }
    }

    /// Update range
    //update [ul,ur] by val
    // keep a lazy at that node
    void update(ll p, ll val, ll ul, ll ur, ll L, ll R){
        if (ul > ur){
            return;
        }

        if (ul == L && ur == R){
            S[p] += val; //notice we keep (add) lazy in a node
        }
        else{
            ll mid = (L+R)/2;
            update(p*2, val, ul, MIN(ur, mid), L, mid);
            update(p*2+1, val, MAX(ul, mid+1), ur, mid +1, R);
        }
    }


    ll query(ll p, ll ql, ll qr, ll L, ll R){
        // [ql...qr] is outside [L...R]
        if (ql > qr)
            return INF; //returns INF so, doesn't hamper with other part values

        if (ql == L && qr == R)
            return T[p];

        ll mid = (L+R)/2;
        ll left = query(p*2, ql, MIN(qr, mid), L, mid);
        ll right = query(p*2+1, MAX(ql, mid+1), qr, mid+1, R);
        /// now combine from left and right.. this is the combine function part
        return MIN(left, right);
    }

    /// PROPAGATION
    // lazy push
    void push(int p) {
        ll val = S[p];

        //update the (maximums) of children
        T[p*2] += val;
        T[p*2 + 1] += val;

        //pass the lazys to children
        S[p*2] += val;
        S[p*2 + 1] += val;

        //remove the current node lazy
        S[p] = 0;
    }

    //update node u -> val
    void update(ll p, ll ul, ll ur, ll val, ll L, ll R){
        if (ul > ur)
            return;

        if (ul == L && ur == R){
            S[p] += val;
            T[p] += val;
            return;
        }

        push(p);

        ll mid = (L+R)/2;

        update(p*2, ul, min(ur, mid), val, L, mid);    //update left segment
        update(p*2+1, max(ul, mid+1), ur, val, mid +1, R);  //right segment

        T[p] = max(T[p*2], T[p*2 + 1]); //propagate up
    }

    /// NUMBER THEORY
    int phi(int n) {
        int result = n;
        for (int i = 2; i  i = n; i++) {
            if (n % i == 0) {
                while (n % i == 0)
                    n = i;
                result -= result  i;
            }
        }
        if (n  1)
            result -= result  n;
        return result;
    }

    vi primes = {0};    // 1-based, dummy first
    map<ll, ll> primeMap;
    vi prePrimes;

    void sieve(){
        ll LIM = 100000;
        vector<bool> is_prime(LIM+1, true);
        prePrimes = vi(LIM+1, 0);

        is_prime[0] = is_prime[1] = false;
        for (ll i = 2; i <= LIM; i++) {
            if (is_prime[i]) {
                primeMap[i] = primes.size();
                primes.push_back(i);

                for (ll j = i * i; j <= LIM; j += i)
                    is_prime[j] = false;
            }
            prePrimes[i] = primes.size();
        }
    }

    vii to_primes(ll x){
        ll p = primes[1];   // 1-based
        ll i = 1;
        vii V;
        while (x != 1 && p * p <= x){
            ll z = 0;
            while (x % p == 0)
            {
                z++;
                x/= p;
            }
            if (z > 0)
                V.push_back({i, z}); //just push index
            p = primes[++i];
        }
        if (x != 1)
            V.push_back({primeMap[x], 1});  // the remaining num itself is prime

        return V;
    }


    /// GEOMETRY
    /// PICK => A = I + B/2 – 1

    struct pt {
        ll x, y;
        pt(ll _x, ll _y){
            x = _x;
            y = _y;
        }
    };

    bool operator<(const pt &a, const pt &b){
        if (a.x < b.x)
            return true;
        if (a.x == b.x && a.y < b.y)
            return true;

        return false;
    }

    vector<pt> all_points;
    vector<ll> dist;

    int orientation(pt a, pt b, pt c) {
        ll v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
        if (v < 0) return -1; // clockwise
        if (v > 0) return +1; // counter-clockwise
        return 0;
    }

    bool cw(pt a, pt b, pt c) {
        int o = orientation(a, b, c);
        return o <= 0;
    }
    bool ccw(pt a, pt b, pt c) {
        int o = orientation(a, b, c);
        return o >= 0;   /// IF points on line are to be included then, >=
    }

    void convex_hull(vector<pt>& a) {
        if (a.size() == 1)
            return;

        sort(a.begin(), a.end(), [](pt a, pt b) {
            return make_pair(a.x, a.y) < make_pair(b.x, b.y);
        });
        pt p1 = a[0], p2 = a.back();
        vector<pt> up, down;
        up.push_back(p1);
        down.push_back(p1);
        for (int i = 1; i < (int)a.size(); i++) {
            if (i == a.size() - 1 || cw(p1, a[i], p2)) {
                while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                    up.pop_back();
                up.push_back(a[i]);
            }
            if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
                while (down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                    down.pop_back();
                down.push_back(a[i]);
            }
        }

        a.clear();
        for (int i = 0; i < (int)up.size(); i++)
            a.push_back(up[i]);
        for (int i = down.size() - 2; i > 0; i--)
            a.push_back(down[i]);
    }

    main(){
        ll n, x, y;

        all_points.clear();
        cin >> n;
        for (ll i = 0; i < n; i++){
            cin >> x >> y;
            all_points.push_back(pt(x, y));
        }
        convex_hull(all_points);    /// all points will now contain only convex hull points
        sort(all_points.begin(), all_points.end());
        cout << all_points.size() << endl;
        for (ll i = 0; i < all_points.size(); i++)
            cout << all_points[i].x << " " << all_points[i].y << endl;
    }


    /// POINTS INSIDE CONVEX POLY (hit = no. of pts)
    main(){
        ll n, m, k;
        cin >> n >> m >> k;

        //convex hull
        vector<Point> all_pts;
        vector<Point> up_hull;
        vector<Point> lo_hull;
        ll mini_idx = 0;
        ll maxi_idx = 0;

        ll x, y;
        cin >> x >> y;
        all_pts.push_back(Point(x, y));
        for (ll i = 1; i < n; i++){
            cin >> x >> y;
            if (x < all_pts[mini_idx].x)
                mini_idx = i;
            if (x > all_pts[maxi_idx].x)
                maxi_idx = i;

            all_pts.push_back(Point(x, y));
        }

        //construct upper hull and lower hull separately
        //lower hull
        ll j = mini_idx;
        while (j != maxi_idx){
            lo_hull.push_back(all_pts[j]);
            if (j == n-1)
                j = 0;
            else
                j++;
        }
        lo_hull.push_back(all_pts[j]);  //push the last point

        //upper hull
        j = maxi_idx;
        while (j != mini_idx){
            up_hull.push_back(all_pts[j]);
            if (j == n-1)
                j = 0;
            else
                j++;
        }
        up_hull.push_back(all_pts[j]);
        reverse(up_hull.begin(), up_hull.end());    // x => ascending

        ll hit = 0;
        //bombs
        for (ll i = 0; i < m; i++){
            cin >> x >> y;
            if (x < all_pts[mini_idx].x || x > all_pts[maxi_idx].x)
                continue;
            if (x == all_pts[mini_idx].x){
                ll prev = mini_idx-1;
                ll next = mini_idx+1;
                if (prev == -1)
                    prev = n-1;
                if (next == n)
                    next = 0;

                if (x == all_pts[prev].x && y >= all_pts[mini_idx].y && y <= all_pts[prev].y)
                    hit++;
                else if (x == all_pts[next].x && y <= all_pts[mini_idx].y && y >= all_pts[next].y)
                    hit++;
            }
            else if (x == all_pts[maxi_idx].x){
                ll prev = maxi_idx-1;
                ll next = maxi_idx+1;
                if (prev == -1)
                    prev = n-1;
                if (next == n)
                    next = 0;

                if (x == all_pts[prev].x && y <= all_pts[maxi_idx].y && y >= all_pts[prev].y)
                    hit++;
                else if (x == all_pts[next].x && y >= all_pts[maxi_idx].y && y <= all_pts[next].y)
                    hit++;

            }
            else{
                //find where (which line) the vertical line intersects upper hull and lower hull
                ll f = lower_bound(up_hull.begin(), up_hull.end(), Point(x,y), compare) - up_hull.begin();
                ll p = orientation(up_hull[f-1], Point(x,y), up_hull[f]);

                f = lower_bound(lo_hull.begin(), lo_hull.end(), Point(x,y), compare) - lo_hull.begin();
                ll q = orientation(lo_hull[f-1], Point(x,y), lo_hull[f]);

                if (p != q)
                    hit++;
            }
        }

        if (hit >= k)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    /// Points Inside Simple Polygon
    bool onSegment(pt p, pt q, pt r) {
        if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
            return true;
        return false;
    }
    // returns false if "just" touches
    bool doIntersect(pt p1, pt q1, pt p2, pt q2) {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 == 0 && onSegment(p1, p2, q1)) return false;
        if (o2 == 0 && onSegment(p1, q2, q1)) return false;
        if (o3 == 0 && onSegment(p2, p1, q2)) return false;
        if (o4 == 0 && onSegment(p2, q1, q2)) return false;

        if (o1 != o2 && o3 != o4)
            return true;

        return false;
    }

    // 0 is outside, 1 is inside, 2 is on boundary
    // POLYGON points adjacent
    int isInsidePolygon(vector<pt>& polygon, pt p) {
        int n = polygon.size();
        if (n < 3) return false;  // A polygon must have at least 3 vertices

        pt extreme = {2000000000L, p.y};

        int cnt = 0, i = 0;
        do {
            int next = (i + 1) % n;

            if (orientation(polygon[i], p, polygon[next]) == 0)
                if (onSegment(polygon[i], p, polygon[next]))
                    return 2;

            // EDGE CASE (POINT HIT)
            if (orientation(polygon[i], p, extreme) == 0){
                if (onSegment(p, polygon[i], extreme)){
                    // reset and try again with different ray
                    cnt = 0;
                    i = 0;
                    extreme.y++;
                    continue;
                }
            }

            if (doIntersect(polygon[i], polygon[next], p, extreme))
                cnt++;

            if (next == 0)
                break;
            i = next;
        } while (1);

        return cnt % 2;  // Return 1 if count is odd, 0 otherwise
    }



    /// Polygon Area Intersection
    // triangle area with respect to origin
    dl tri_area(pt a, pt b, pt c){
        return 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    }
    dl poly_area(vector<pt> P){
        dl a = 0;
        ll sz = P.size();
        for (ll i = 0; i < sz; i++){
            ll next = i == sz-1 ? 0 : i +1;
            a += tri_area(pt(0,0), P[i], P[next]);
        }
        return fabs(a);
    }

    vector<Edge> all_edges;
    dl A1, A2;

    // find intersection POINTS OF Polygon P with respect to Q (A2 is area of Q)    O(N^3)?
    void find_intersections(vector<pt> &P, vector<pt> &Q, dl A2){
        // for all lines of P... find intersections with Q
        ll m = P.size();
        ll n = Q.size();

        // for each EDGE <a, b> of polygon P
        for (ll i = 0; i < m; i++){
            ll n1 = (i == m-1 ? 0 : i+1);   //next index of point
            pt a = P[i], b = P[n1]; //two adjacent points of Polygon P

            /// intersection points
            vector<dl> insects;
            // for each Edge <c, d> of polygon Q
            for (ll j = 0; j < n; j++){

                ll n2 = (j == n-1 ? 0 : j+1);
                pt c = Q[j], d = Q[n2];

                // a + t1(b-a)     -> Equation of line <a,b>
                // c + t2(d-c)     -> Equation of line <c,d>
                // a.x + t1(b.x-a.x) = c.x + t2(d.x-c.x)    -> intersection of two equations (t1, t2 variables)
                // t1(b.x-a.x) + t2(c.x-d.x) + (a.x - c.x) = 0
                // t1(b.y-a.y) + t2(c.y-d.y) + (a.y - c.y) = 0

                ///solve for t1, t2
                dl p1 = b.x-a.x, q1 = c.x-d.x, r1 = a.x-c.x;
                dl p2 = b.y-a.y, q2 = c.y-d.y, r2 = a.y-c.y;

                if (fabs(p1/p2 - q1/q2) < eps) //parallel line, no intersection
                    continue;

                dl t1 = (q1*r2-q2*r1)/(p1*q2-p2*q1);
                dl t2 = (r1*p2-r2*p1)/(p1*q2-p2*q1);

                //there is intersection => only if t1, t2 are between [1, eps] because that represent the "segment"
                //cout << i << " x " << j << ": " << t1 << " " << t2 << endl;
                if (t1 > eps && t1 < 1-eps && t2 > eps && t2 < 1-eps){
                    //cout << "pushed" << endl;
                    insects.push_back(t1);
                }
            }

            if (insects.size() > 0){
                sort(insects.begin(), insects.end());

                // f = a + t (b-a)   where t = insects[0]
                pt f = pt(a.x + insects[0]*(b.x-a.x), a.y + insects[0]*(b.y-a.y) ); //first intersection point
                pt M = pt( (a.x + f.x)/ 2, (a.y + f.y)/ 2 );

                /// NOTICE ANOTHER LOOP
                // here we are basically removing segments of edges that are inside the polygon Q
                // If midpoint of segment is not inside Q include that edge
                if (!insidePoly(M, Q, A2))
                    all_edges.push_back(Edge(a, f));

                pt prev = f;
                for (ll k = 1; k < insects.size(); k++){
                    f = pt(a.x + insects[k]*(b.x-a.x), a.y + insects[k]*(b.y-a.y) );    //intersection points
                    pt M = pt( (prev.x + f.x)/ 2, (prev.y + f.y)/ 2 );    // segment between 2 cons. int points

                    if (!insidePoly(M, Q, A2))
                        all_edges.push_back(Edge(prev, f));

                    prev = f;
                }
                M = pt((f.x + b.x) / 2, (f.y+b.y) / 2);
                if (!insidePoly(M, Q, A2))
                    all_edges.push_back(Edge(f, b));

            }
            else{
                // just the whole edge <a,b>
                pt M = pt((a.x+b.x) /2 , (a.y+b.y) / 2);
                if (!insidePoly(M, Q, A2))
                    all_edges.push_back(Edge(a, b));
            }
        }
    }

    dl intersect_area(vector<pt> P, vector<pt> Q){
        all_edges.clear();

        ll m = P.size();
        ll n = Q.size();

        find_intersections(P, Q, A2); //segmentation of P
        find_intersections(Q, P, A1); //segmentation of Q

        ll sz = all_edges.size();

        /// area = union area
        dl area = 0;
        for (ll i = 0; i < sz; i++){

            area += tri_area(pt(0,0), all_edges[i].u, all_edges[i].v);
        }
        dl intersect_area = fabs(A1+A2-fabs(area));  ///intersection area
        return intersect_area;
    }

    main(){
        ll m, n;
        // POLYGON P
        cin >> m;
        vector<pt> P(m);
        for (ll i = 0; i < m ; i++)
            cin >> P[i].x >> P[i].y;

        // POLYGON Q
        cin >> n;
        vector<pt> Q(n);
        for (ll i = 0; i < n; i++)
            cin >> Q[i].x >> Q[i].y;

        A1 = poly_area(P);
        A2 = poly_area(Q);
    }


    /// GRAPHS
    main(){
        front_adj = vector<vector<Edge>>(n+1);
        rev_adj = vector<vector<Edge>>(n+1);

        for (ll i = 0; i < m; i++){
            ll u, v, w;
            cin >> u >> v >> w;
            front_adj[u].push_back(Edge(v, w));   //one-way
            rev_adj[v].push_back(Edge(u, w));
        }
    }
    /// Djikstra
    void djikstra(vector<ll> &dist, ll s, vector<vector<Edge>> adj){
        /// s is the source

        priority_queue<PII, vector<PII>, greater<PII>> PQ;
        dist[s] = 0;
        PQ.push({0, s}); //0 distance, 1 is the city

        while (!PQ.empty()){
            PII t = PQ.top();
            PQ.pop();

            if (dist[t.ss] != t.ff) //if not equal, that means this t node is old
                continue;

            for (Edge e : adj[t.ss]){
                if (e.w + t.ff < dist[e.v])
                {
                    dist[e.v] = e.w + t.ff;
                    PQ.push({dist[e.v],e.v});
                }
            }
        }
    }

    /// BELLMAN-FORD
    for (ll i = 0; i < n-1; i++){
        for (Edge e: edges){
            if (e.w + dist[e.u] < dist[e.v])
                dist[e.v] = e.w + dist[e.u];
        }
    }

    /// FLOYD-WARSHALL
    main(){
        ll n, m, q;
        cin >> n >> m >> q;
        for (ll i = 0; i < m; i++){
            ll u, v, w;
            cin >> u >> v >> w;
            dist[u][v] = min(w, dist[u][v]);
            dist[v][u] = dist[u][v];
        }

        for (ll k = 1; k <= n; k++){
            for (ll i = 1; i <= n; i++){
                for (ll j = 1; j <= n; j++){
                    ll alt_dist = dist[i][k] + dist[k][j];
                    if (alt_dist < dist[i][j]){
                        dist[i][j] = alt_dist;
                        dist[j][i] = alt_dist;
                    }
                }
            }
        }
    }


    /// TOPOLOGICAL SORT
    //returns true if cycle found, else false   (u = current node, p = parent)
    ll dfs(ll u, ll p){
        visited[u] = 1; //start of dfs from this node
        pre[u] = p;

        for (ll i = 0; i < adj[u].size(); i++){
            ll v = adj[u][i];


            if (visited[v]){
                pre[v] = u;

                //cycle found
                if (visited[v] == 1)
                    return v;
            }
            else
            {
                ll cycle_node = dfs(v, u);
                if (cycle_node)
                    return cycle_node;
            }
        }

        T.push_back(u);
        visited[u] = 2; //end of dfs from this node
        return 0;
    }


    main(){
        ll n, m;
        cin >> n >> m;
        for (ll i = 0; i < m; i++){
            ll u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        ll cycle_node = 0;
        for (ll i = 1; i <= n; i++){
            if (!visited[i]){
                cycle_node = dfs(i, 0);
                if (cycle_node)
                    break;
            }
        }

        if (cycle_node)
            cout << "IMPOSSIBLE" << endl;
        else
        {
            reverse(T.begin(), T.end());
            vector<ll> steps(n+1, -1);  //-1 means unreachable
            vector<ll> pre(n+1, 0);
            steps[1] = 0;
            ll i;
            //LOCATE node 1
            for (i = 0; i < n; i++)
                if (T[i] == 1)
                    break;

            // from node 1 start relaxing others (only in forward direction as already top sorted)
            for (; i < n; i++){
                // take nodes from top sorted list 1 by 1; starting from node 1
                ll u = T[i];
                for (ll v : adj[u]){
                    if (steps[u] == -1)   //not reachable
                        continue;

                    if (steps[u] + 1 > steps[v]){ //negative steps (as we want longest route) // see CSES subs
                        steps[v] = steps[u] + 1;
                        pre[v] = u;
                    }
                }
            }

            if (steps[n] == -1)
                cout << "IMPOSSIBLE" << endl;
            else{
                cout << steps[n]+1 << endl;

                vector<ll> path;
                path.push_back(n);
                ll x = pre[n];
                while (x != 1){
                    path.push_back(x);
                    x = pre[x];
                }
                path.push_back(1);
                reverse(path.begin(), path.end());

                for (ll pp : path)
                    cout << pp << " ";
                cout << endl;
            }
        }
    }


    /// MST PRIM
    // MST returns minimum cost (return -1 if not connected)
    ll prim(vector<vector<Edge>> adj){

        ll ret = 0;

        priority_queue<PII, vector<PII>, greater<PII>> PQ;


        vector<bool> taken(adj.size());
        vector<ll> cost(adj.size(), INF);
        PQ.push({0, 1}); //0 distance, 1 node
        cost[1] = 0;

        while (!PQ.empty()){
            PII t = PQ.top();
            PQ.pop();

            if (taken[t.ss])
                continue;
            taken[t.ss] = true;
            ret += t.ff;

            for (Edge e : adj[t.ss]){
                // less weight edge to connect e.v
                if (e.w < cost[e.v])
                {
                    PQ.push({e.w,e.v});
                    cost[e.v] = e.w;    // update the better cost
                }
            }
        }

        for (ll i = 1; i < adj.size(); i++){
            if (cost[i] == INF){
                ret = -1;
                break;
            }
        }
        return ret;
    }





