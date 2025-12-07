#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll INF = 10000000000000000;   //10^16 ... will not be bigger than this

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

    /*
    for (int i = 0; i < a.size(); i++){
        printf("h: %d %d\n", a[i].x, a[i].y);
    }
    */
}

/*
ll euler_distance(pt a, pt b){
    ll x = a.x - b.x;
    ll y = a.y - b.y;
    return x*x + y*y;
}
*/

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //freopen ("input.txt","r",stdin);
    //freopen ("output.txt","w",stdout);

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

    return 0;
}
