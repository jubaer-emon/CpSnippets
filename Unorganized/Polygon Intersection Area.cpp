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