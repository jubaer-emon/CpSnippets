
dl f(dl m) {
    return ;
}

dl ternary_search(dl l, dl r) {
    while (fabs(l-r) > EPS) {
        dl m1 = l + (r - l) / 3;
        dl m2 = r - (r - l) / 3;
        dl f1 = f(m1);
        dl f2 = f(m2);
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return l;  //return the maximum of f(x) in [l, r]
}

