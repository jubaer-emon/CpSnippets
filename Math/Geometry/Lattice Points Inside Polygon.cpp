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