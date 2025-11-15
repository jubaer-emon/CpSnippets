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


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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

    return 0;
}
