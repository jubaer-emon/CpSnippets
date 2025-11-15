#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define dl double long
#define mod 998244353
#define INF 1000000000000000000  //10e18
#define inf9 1000000000 //10e9
#define ff first
#define ss second

#define pii pair<int, int>
#define PII pair<ll, ll>
#define vi vector<int>
#define VI vector<ll>
#define vii vector<pii>
#define VII vector<PII>
#define all(x) x.begin(), x.end()

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

void print_stack(stack<ll> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << a.top() << " ";
        a.pop();
    }
    cout << endl;
}
void print_stack(stack<PII> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << "(" << a.top().ff << ", " << a.top().ss << "); ";
        a.pop();
    }
    cout << endl;
}

void print_queue(queue<ll> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << a.front() << " ";
        a.pop();
    }
    cout << endl;
}
void print_queue(queue<PII> a){
    cout << "DEBUG: ";
    while (!a.empty()){
        cout << "(" << a.front().ff << ", " << a.front().ss << "); ";
        a.pop();
    }
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


#define N 200001
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

bool cmp(const PII& a, const PII& b) {
    return a.ff < b.ff;
}

struct cmpXY{
    bool operator()(const PII& a, const PII& b) const {
        if (a.ff != b.ff)
            return a.ff < b.ff; // descending
        return a.ss < b.ss;
    }
};

struct cmpX{
    bool operator()(const PII& a, const PII& b) const {
        if (a.ff != b.ff)
            return a.ff > b.ff; // descending
        return a.ss > b.ss;
    }
};

struct cmpY{
    bool operator()(const PII& a, const PII& b) const {
        if (a.ss != b.ss)
            return a.ss > b.ss; // descending
        return a.ff > b.ff;
    }
};

/// MERGE SORT

ll merge(vector<ll> &arr, vector<ll> &temp, ll left, ll mid, ll right) {
    ll i = left, j = mid, k = left;
    ll inv_count = 0;

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);  // all remaining in left half are > arr[j]
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (ll idx = left; idx <= right; idx++)
        arr[idx] = temp[idx];

    return inv_count;
}

ll _mergeSort(vector<ll> &arr, vector<ll> &temp, ll left, ll right) {
    ll inv_count = 0;
    if (right > left) {
        ll mid = (left + right) / 2;

        inv_count += _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

ll mergeSort(vector<ll> &arr) {
    vector<ll> temp(arr.size());
    return _mergeSort(arr, temp, 0, arr.size() - 1);
}


// Driver code
int main()
{
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++)
        cin >> a[i];
    ll ans = mergeSort(a);
    cout << " Number of inversions are " << ans;
    return 0;
}

// This is code is contributed by rathbhupendra
