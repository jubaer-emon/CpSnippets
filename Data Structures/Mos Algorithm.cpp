void remove_el(idx){

}
void add_el(idx){

}
ll get_answer(){

};

ll block_size;

struct Query {
    ll l, r, idx;
    Query(ll _l, ll _r, ll _i){
        l = _l;
        r = _r;
        idx = _i;
    }

    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

void mo_s_algorithm(vector<Query> &queries, vector<bool> &answers) {
    answers = vector<bool> (queries.size());
    sort(queries.begin(), queries.end());

    odds = 0;    // how many with odd occurences

    ll cur_l = 0;
    ll cur_r = -1;

    for (Query q : queries) {
        if ( (q.r - q.l + 1) % 2){
            answers[q.idx] = false;
            continue;
        }

        while (cur_l > q.l) {
            cur_l--;
            add_el(cur_l);   // add
        }
        while (cur_r < q.r) {
            cur_r++;
            add_el(cur_r);   // add
        }
        while (cur_l < q.l) {
            remove_el(cur_l);   // remove
            cur_l++;
        }
        while (cur_r > q.r) {
            remove_el(cur_r);   // remove
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
}