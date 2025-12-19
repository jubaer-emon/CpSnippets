#include <bits/stdc++.h>
#define ll long long
#define M 1000000007

using namespace std;

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

/*
//p = pattern, t = text
//returns a list of occurence positions
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
*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    ll n = s.length();
    vector<ll> pi;
    prefix_function(s, pi);

    ll cur = n-1;
    vector<ll> ans;
    while(pi[cur] != 0){
        ans.push_back(pi[cur]);
        cur = pi[cur]-1;    // -1 for the index
    }

    reverse(ans.begin(), ans.end());
    for (ll p : ans)
        cout << p << " ";
    return 0;
}
