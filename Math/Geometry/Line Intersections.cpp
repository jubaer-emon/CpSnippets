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

bool onSegment(pt p, pt q, pt r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(pt a, pt b, pt c) {
    ll v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
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


/* VECTOR METHOD
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
*/