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
#define INF 10000000000000  //10e13
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

struct pt{
    dl x, y;
    pt (){}
    pt(dl _x, dl _y){
        x = _x;
        y = _y;
    }
};

bool onSegment(pt p, pt q, pt r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(pt a, pt b, pt c) {
    dl v = a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

bool doIntersect(pt p1, pt q1, pt p2, pt q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    if (o1 != o2 && o3 != o4)
        return true;

    return false;
}

// 0 is outside, 1 is inside, 2 is on boundary
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

// triangle area with respect to origin
dl tri_area(pt a, pt b, pt c){
    return 0.5L * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
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

ll pointsOnBoundary(vector<pt>& polygon){
    ll cnt = 0;
    ll n = polygon.size();
    for (ll i = 0; i < n; i++){
        ll next = (i+1) % n;
        ll dx = abs(polygon[i].x - polygon[next].x);
        ll dy = abs(polygon[i].y - polygon[next].y);
        cnt += gcd(dx, dy) + 1;
    }
    return cnt-n;
}

ll pointsInsidePolygon(vector<pt>& polygon){
    // pick's theorem => A = i + b/2 - 1
    dl A = poly_area(polygon);
    ll b = pointsOnBoundary(polygon);
    ll i = A - b/2 + 1;
    return i;
}

int main() {

    ll n;
    cin >> n;

    vector<pt> polygon(n);
    for (ll i = 0; i < n; i++)
        cin >> polygon[i].x >> polygon[i].y;

    dl A = poly_area(polygon);
    ll b = pointsOnBoundary(polygon);
    ll i = A - b/2 + 1;
    cout << i << " " << b << endl;
    return 0;
}
