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
    //cout << sz << endl;

    /// area = union area
    dl area = 0;
    for (ll i = 0; i < sz; i++){
        //cout << "(" << all_edges[i].u.x << ", " << all_edges[i].u.y << ") - ";
        //cout << "(" << all_edges[i].v.x << ", " << all_edges[i].v.y << ")" << endl;

        area += tri_area(pt(0,0), all_edges[i].u, all_edges[i].v);
    }

    dl intersect_area = fabs(A1+A2-fabs(area));  ///intersection area
    return intersect_area;
}


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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


    return 0;
}
