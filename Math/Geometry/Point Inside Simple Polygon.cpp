// 0 is outside, 1 is inside, 2 is on boundary
int isInsidePolygon(vector<pt>& polygon, pt p) {
    int n = polygon.size();
    if (n < 3) return false;  // A polygon must have at least 3 vertices

    pt extreme = {2000000000L, p.y};

    int cnt = 0, i = 0;
    do {
        int next = (i + 1) % n;

        if (orientation(polygon[i], p, polygon[next]) == 0)
            if (onSegment(polygon[i], p, polygon[next]))
                return 2;

        // EDGE CASE (POINT HIT)
        if (orientation(polygon[i], p, extreme) == 0){
            if (onSegment(p, polygon[i], extreme)){
                // reset and try again with different ray
                cnt = 0;
                i = 0;
                extreme.y++;
                continue;
            }
        }

        if (doIntersect(polygon[i], polygon[next], p, extreme))
            cnt++;

        if (next == 0)
            break;
        i = next;
    } while (1);

    return cnt % 2;  // Return 1 if count is odd, 0 otherwise
}