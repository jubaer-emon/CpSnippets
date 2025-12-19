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

//bombs
for (ll i = 0; i < m; i++){
    cin >> x >> y;
    if (x < all_pts[mini_idx].x || x > all_pts[maxi_idx].x)
        continue;
    if (x == all_pts[mini_idx].x){
        ll prev = (mini_idx+n-1);
        ll next = mini_idx+1;
        if (prev == -1) prev = n-1;
        if (next == n) next = 0;

        if (x == all_pts[prev].x && y >= all_pts[mini_idx].y && y <= all_pts[prev].y) hit++;
        else if (x == all_pts[next].x && y <= all_pts[mini_idx].y && y >= all_pts[next].y) hit++;
    }
    else if (x == all_pts[maxi_idx].x){
        ll prev = maxi_idx-1;
        ll next = maxi_idx+1;
        if (prev == -1) prev = n-1;
        if (next == n) next = 0;

        if (x == all_pts[prev].x && y <= all_pts[maxi_idx].y && y >= all_pts[prev].y) hit++;
        else if (x == all_pts[next].x && y >= all_pts[maxi_idx].y && y <= all_pts[next].y) hit++;
    }
    else{
        //find where (which line) the vertical line intersects upper hull and lower hull
        ll f = lower_bound(up_hull.begin(), up_hull.end(), Point(x,y), compare) - up_hull.begin();
        ll p = orientation(up_hull[f-1], Point(x,y), up_hull[f]);
        f = lower_bound(lo_hull.begin(), lo_hull.end(), Point(x,y), compare) - lo_hull.begin();
        ll q = orientation(lo_hull[f-1], Point(x,y), lo_hull[f]);
        if (p != q) hit++;
    }
}