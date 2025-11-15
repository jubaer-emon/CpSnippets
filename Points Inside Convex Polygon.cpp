#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 10000000000
#define PII pair<ll, ll>
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define eps 0.000001

ll MIN (ll a, ll b){
    return a < b ? a : b;
}

ll MAX(ll a, ll b){
    return a > b ? a : b;
}



struct Point{
    ll x, y;
    Point(ll _x, ll _y){
        x = _x;
        y = _y;
    }
};

bool compare(Point a, Point b){
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

int orientation(Point a, Point b, Point c) {
    double v = a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    ll n, m, k;
    cin >> n >> m >> k;

    //convex hull
    vector<Point> all_pts;
    vector<Point> up_hull;
    vector<Point> lo_hull;
    ll mini_idx = 0;
    ll maxi_idx = 0;

    ll x, y;
    cin >> x >> y;
    all_pts.push_back(Point(x, y));
    for (ll i = 1; i < n; i++){
        cin >> x >> y;
        if (x < all_pts[mini_idx].x)
            mini_idx = i;
        if (x > all_pts[maxi_idx].x)
            maxi_idx = i;

        all_pts.push_back(Point(x, y));
    }

    //construct upper hull and lower hull separately
    //lower hull
    ll j = mini_idx;
    while (j != maxi_idx){
        lo_hull.push_back(all_pts[j]);
        if (j == n-1)
            j = 0;
        else
            j++;
    }
    lo_hull.push_back(all_pts[j]);  //push the last point

    //upper hull
    j = maxi_idx;
    while (j != mini_idx){
        up_hull.push_back(all_pts[j]);
        if (j == n-1)
            j = 0;
        else
            j++;
    }
    up_hull.push_back(all_pts[j]);
    reverse(up_hull.begin(), up_hull.end());    // x => ascending

    ll hit = 0;
    //ll prev_hit = 0;

    //cout << up_hull.size() << " c " << lo_hull.size() << endl;
    //cout << all_pts[mini_idx].x << " b "<< all_pts[maxi_idx].x << endl;

    //bombs
    for (ll i = 0; i < m; i++){
        cin >> x >> y;
        if (x < all_pts[mini_idx].x || x > all_pts[maxi_idx].x)
            continue;
        if (x == all_pts[mini_idx].x){
            ll prev = mini_idx-1;
            ll next = mini_idx+1;
            if (prev == -1)
                prev = n-1;
            if (next == n)
                next = 0;

            if (x == all_pts[prev].x && y >= all_pts[mini_idx].y && y <= all_pts[prev].y)
                hit++;
            else if (x == all_pts[next].x && y <= all_pts[mini_idx].y && y >= all_pts[next].y)
                hit++;
        }
        else if (x == all_pts[maxi_idx].x){
            ll prev = maxi_idx-1;
            ll next = maxi_idx+1;
            if (prev == -1)
                prev = n-1;
            if (next == n)
                next = 0;

            if (x == all_pts[prev].x && y <= all_pts[maxi_idx].y && y >= all_pts[prev].y)
                hit++;
            else if (x == all_pts[next].x && y >= all_pts[maxi_idx].y && y <= all_pts[next].y)
                hit++;

        }
        else{
            //find where (which line) the vertical line intersects upper hull and lower hull
            ll f = lower_bound(up_hull.begin(), up_hull.end(), Point(x,y), compare) - up_hull.begin();
            ll p = orientation(up_hull[f-1], Point(x,y), up_hull[f]);

            f = lower_bound(lo_hull.begin(), lo_hull.end(), Point(x,y), compare) - lo_hull.begin();
            ll q = orientation(lo_hull[f-1], Point(x,y), lo_hull[f]);

            if (p != q)
                hit++;
        }

        //if (prev_hit != hit)
            //cout << x << " x " << y << endl;
        //prev_hit = hit;
    }

    //cout << hit << endl;

    if (hit >= k)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
