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