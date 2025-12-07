///https://codeforces.com/contest/1942/problem/D

#include <bits/stdc++.h>
using namespace std;
#define ll int
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

priority_queue<ll> dp[1001];
stack<ll> tmp[1001];
ll a[1001][1001];

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    dp[0].push(0);

    while (t--){
        ll n, k;
        cin >> n >> k;
        for (ll i = 1; i <= n; i++){
            while (!dp[i].empty())
                dp[i].pop();

            for (ll j = i; j <= n; j++){
                cin >> a[i][j];
            }
        }


        for (ll i = 1; i <= n; i++){
            priority_queue<PII> pq;  // number & index which list used
            pq.push({a[1][i], -1});
            // need top k elements from (i-1) lists...
            // first let's take top elements from each list
            for (ll j = 0; j <= i-1; j++){
                ll f = dp[j].top();
                tmp[j].push(dp[j].top());

                dp[j].pop();

                if (j < i-1)
                    f += a[j+2][i];
                pq.push({f, j});
            }

            // now fill k or available elements into dp[i]
            while (dp[i].size() < k && !pq.empty()){
                PII p = pq.top();
                pq.pop();

                dp[i].push(p.ff);

                // balance pq by inserting another from the list (from which removed)
                if (p.ss != -1 && !dp[p.ss].empty()){
                    ll f = dp[p.ss].top();
                    tmp[p.ss].push(f);
                    dp[p.ss].pop();

                    if (p.ss < i-1)
                        f += a[p.ss+2][i];

                    pq.push({f, p.ss});
                }
            }

            // now restore the previous dp's
            for (ll j = 0; j <= i-1; j++){
                while (!tmp[j].empty()){
                    dp[j].push(tmp[j].top());
                    tmp[j].pop();
                }
            }
        }

        // ANSWER
        while(!dp[n].empty()){
            cout << dp[n].top() << " ";
            dp[n].pop();
        }

        cout << endl;
    }

    return 0;
}
