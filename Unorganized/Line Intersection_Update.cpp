#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 22000
#define PII pair<ll, ll>
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define eps 0.00000000001
#define dl long long

ll MIN (dl a, dl b){
    return a < b ? a : b;
}

ll MAX(dl a, dl b){
    return a > b ? a : b;
}

struct pt{
    dl x, y;
    pt (){}
    pt(dl _x, dl _y){
        x = _x;
        y = _y;
    }
};

struct Edge{
    pt u, v;
    Edge(){}
    Edge(pt _u , pt _v){
        u = _u;
        v = _v;
    }
};


bool compare(pt a, pt b){
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

dl dist(pt a, pt b){
    dl dx = a.x-b.x;
    dl dy = a.y-b.y;
    return sqrt(dx*dx + dy*dy);
}

bool operator==(pt const &a, pt const &b){
    return (dist(a,b) < eps);
}


/*
// triangle area with respect to origin
dl tri_area(pt a, pt b, pt c){
    return 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

/// if a point is inside a polygon => area is actual area of polygon (pre-calculated)
bool insidePoly(pt T, vector<pt> P, dl area){
    dl a = 0;
    ll sz = P.size();
    for (ll i = 0; i < sz; i++){
        ll next = i == sz-1 ? 0 : i +1;
        a += fabs(tri_area(T, P[i], P[next]));  //notice the "fabs"
    }

    return (fabs(a-area) < eps);
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
*/

 bool onSegment(pt p, pt q, pt r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(pt p, pt q, pt r) {
    ll val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(pt p1, pt q1, pt p2, pt q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t;
    cin >> t;
    dl x1, y1, x2, y2, x3, y3, x4, y4;

    while (t--){
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        pt a = {x1, y1}, b = {x2, y2};

        pt c = {x3, y3}, d = {x4, y4};
        if (doIntersect(a, b, c, d))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

    }

    return 0;
}
