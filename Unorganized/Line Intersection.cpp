#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 22000
#define PII pair<ll, ll>
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define eps 0.0000001
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

        // a + t1(b-a)     -> Equation of line <a,b>
        // c + t2(d-c)     -> Equation of line <c,d>
        // a.x + t1(b.x-a.x) = c.x + t2(d.x-c.x)    -> intersection of two equations (t1, t2 variables)
        // t1(b.x-a.x) + t2(c.x-d.x) + (a.x - c.x) = 0
        // t1(b.y-a.y) + t2(c.y-d.y) + (a.y - c.y) = 0

        ///solve for t1, t2
        dl p1 = b.x-a.x, q1 = c.x-d.x, r1 = a.x-c.x;
        dl p2 = b.y-a.y, q2 = c.y-d.y, r2 = a.y-c.y;

        if ((fabs(p2) < eps && fabs(q2) < eps) || fabs(p1/p2 - q1/q2) < eps){ //parallel line
            // if two lines superimpose,
            // either ac+cb = ab or ad+db = ab or ca+ad = cd
            if ( fabs(dist(a, c) + dist(c, b) - dist(a, b) ) <  eps
                ||  fabs(dist(a, d) + dist(d, b) - dist(a, b) ) <  eps
                || fabs(dist(c, a) + dist(a, d) - dist(c, d) ) <  eps)
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            continue;
        }

        dl t1 = (q1*r2-q2*r1)/(p1*q2-p2*q1);
        dl t2 = (r1*p2-r2*p1)/(p1*q2-p2*q1);

        //there is intersection => only if t1, t2 are between [1, eps] because that represent the "segment"
        //cout << i << " x " << j << ": " << t1 << " " << t2 << endl;
        if (t1 > -eps && t1 < 1+eps && t2 > -eps && t2 < 1+eps)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}
