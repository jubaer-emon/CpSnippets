///https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/D
struct node{
    node *nxt = nullptr;
    ll val;
    node(ll _v){
        val = _v;
    }
};
struct LI{
    node *head = nullptr, *tail = nullptr;
};

vector<LI*> p;

// b gonna own
void unionp(ll a, ll b){
    if (p[b]->head == nullptr)
        p[b]->head = p[a]->head;
    else
        p[b]->tail->nxt = p[a]->head;

    p[b]->tail = p[a]->tail;
    p[a]->head = nullptr;
    p[a]->tail = nullptr;
}

/*
for (ll i = 0; i < n; i++){
    node *nd = new node(i);
    LI *l = new LI;
    l->head = nd;
    l->tail = nd;
    p.push_back(l);
}
*/