ll T[1000000];  // at least 2*n size (good to go 4*n, because we use 2*n and 2*n+1 stuffs) for segment trees
ll S[1000000];  // we only need lazy information here

// lazy push
void push(int p) {
    ll val = S[p];

    //update the children
    T[p*2] += val;
    T[p*2 + 1] += val;

    //pass the lazys to children
    S[p*2] += val;
    S[p*2 + 1] += val;

    //remove the current node lazy
    S[p] = 0;
}

//update [ul,ur] by val
/// keep a lazy at that node
void update(ll p, ll ul, ll ur, ll val, ll L, ll R){
    if (ul > ur)
        return;

    if (ul == L && ur == R){
        S[p] += val;
        T[p] += val;
        return;
    }

    push(p);

    ll mid = (L+R)/2;

    update(p*2, ul, min(ur, mid), val, L, mid);    //update left segment
    update(p*2+1, max(ul, mid+1), ur, val, mid +1, R);  //right segment

    T[p] = max(T[p*2], T[p*2 + 1]); //propagate up
}

ll query(ll p, ll ql, ll qr, ll L, ll R){
    // [ql...qr] is outside [L...R]
    if (ql > qr)
        return -INF; // [returns INF so, doesn't hamper with other part values]

    if (ql == L && qr == R)
        return T[p];

    push(p);

    ll mid = (L+R)/2;
    ll left = query(p*2, ql, min(qr, mid), L, mid);
    ll right = query(p*2+1, max(ql, mid+1), qr, mid+1, R);
    /// now combine from left and right.. this is the combine function part
    return max(left, right);
}