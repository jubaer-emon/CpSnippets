#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 22000
#define PII pair<ll, ll>
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define eps 0.0001
#define dl double

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

// triangle area with respect to origin
dl tri_area(pt a, pt b, pt c){
    return 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

/*
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
*/

dl poly_area(vector<pt> P){
    dl a = 0;
    ll sz = P.size();
    for (ll i = 0; i < sz; i++){
        ll next = i == sz-1 ? 0 : i +1;
        a += tri_area(pt(0,0), P[i], P[next]);
    }
    return fabs(a);
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;

    // POLYGON P
    cin >> n;
    vector<pt> P(n);
    for (ll i = 0; i < n ; i++)
        cin >> P[i].x >> P[i].y;

    cout << poly_area(P) << endl;


    return 0;
}
