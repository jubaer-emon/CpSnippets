
struct node {
    ll mn,mx,sum;
    bool isInc;
 
    node() : mn(1e9+1),mx(0),sum(0),isInc(true) {}
    node(ll x) : mn(x),mx(x),sum(x),isInc(true) {}
    node(node& l, node& r) :
        mn(min(l.mn,r.mn)),
        mx(max(l.mx,r.mx)),
        sum(l.sum+r.sum),
        isInc(l.isInc && r.isInc && l.mx <= r.mn) {};
 
    friend ostream& operator<<(ostream& os, const node& n) {
        os << "mn" << n.mn << "mx" << n.mx << "sm" << n.sum << "i" << n.isInc;
        return os;
    }
};
 
struct segtree {
    ll n;
    vector<node> st;
    vector<ll>& a;
    ll curmax;
 
    segtree(ll n, vector<ll>& a) : n(n),a(a),st(4*n) {
        build(0,0,n-1);
    }
    void build(ll v, ll tl, ll tr) {
        if (tl == tr) {
            st[v] = node(a[tl]);
            return;
        }
 
        ll tm = (tl+tr)/2;
        build(v*2+1, tl, tm);
        build(v*2+2, tm+1, tr);
        st[v] = node(st[v*2+1], st[v*2+2]);
    }
 
    /*void update(int pos, int val) {
        update(pos,val,0,0,n-1);
    }
    void update(int pos, int val, int v, int tl, int tr) {
        if (tl == tr) {
            st[v] = val;
            return;
        }
 
        int tm = (tl+tr)/2;
        if (pos <= tm) update(pos,val,v*2+1,tl,tm);
        else update(pos,val,v*2+2,tm+1,tr);
        st[v] = combine(st[v*2+1], st[v*2+2]);
    }*/
 
    ll rng_query(ll ql,ll qr) {
        curmax = a[ql];
        return rng_query(ql,qr,0,0,n-1);
    }
    ll rng_query(ll ql,ll qr,ll v,ll tl,ll tr) {
        if (ql <= tl && tr <= qr) {
            if (curmax >= st[v].mx) {
                return curmax*(tr-tl+1)-st[v].sum;
            }
            if (st[v].mx == a[tl]) {
                curmax = st[v].mx;
                return st[v].mx*(tr-tl+1)-st[v].sum;
            }
            if (curmax <= st[v].mn && st[v].isInc) {
                curmax = st[v].mx;
                return 0;
            }
        }
        if (tr < ql || tl > qr) {
            return 0;
        }
 
        ll tm = (tl+tr)/2;
        ll lres = rng_query(ql, qr, v*2+1, tl, tm);
        //cout << "max is " << curmax << " after [" << tl << "," << tm << "] with " << lres << "ops \n";
        ll rres = rng_query(ql, qr, v*2+2, tm+1, tr);
        //cout << "max is " << curmax << " after [" << tm+1 << "," << tr << "] with " << rres << "ops \n";
        return lres+rres;
    }
 
    /*int pnt_query(int k, int v=0, int tl=0, int tr=n-1) {
        if (k < tl) return tl-k+st[v].lmin;
        if (tr < k) return st[v].rmin+k-tr;
        if (tl == k && tr == k) return st[v].lmin;
 
        int tm = (tl+tr)/2;
        return min(pnt_query(k,v*2+1,tl,tm), pnt_query(k,v*2+2,tm+1,tr));
    }*/
    void print() {
        #ifdef LOCAL
        print(0, 0, 0, 0, n-1);
        #endif
    }
    void print(bool isL, int lvl, int v, int tl, int tr) {
        char head = isL? '/' : '\\';
        ll spacing = 16;
        if (tl == tr) {
            cout << string(lvl*spacing, ' ') << head << st[v] << " |" << endl;
            return;
        }
 
        int tm = (tl+tr)/2;
        print(1, lvl+1, v*2+1, tl, tm);
        cout << string(lvl*spacing, ' ') << head << st[v] << " <" << endl;
        print(0, lvl+1, v*2+2, tm+1, tr);
    }
};

