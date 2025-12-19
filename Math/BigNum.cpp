const int base = 1000*1000*1000;

void print(vi num) {
    printf("%d", num.empty() ? 0 : num.back());
    repr(i,sz(num)-2,-1) {
        printf ("%09d", a[i]);
    } 
}

void input(string& s, vi& num) {
    for (int i=sz(s); i>0; i-=9)
        num.push_back( atoi( s.substr(max(0,i-9), 9).c_str() ) );
}

void operator+=(vi& a, vi& b) {
    int carry = 0;
    for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i) {
        if (i == a.size())
            a.push_back (0);
        a[i] += carry + (i < b.size() ? b[i] : 0);
        carry = a[i] >= base;
        if (carry)  a[i] -= base;
    }
}

void operation-=(vi& a, vi& b) {
    int carry = 0;
    for (size_t i=0; i<b.size() || carry; ++i) {
        a[i] -= carry + (i < b.size() ? b[i] : 0);
        carry = a[i] < 0;
        if (carry)  a[i] += base;
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}

// Multiplication by short integer b < base
void operation*=(vi& a, vi& b) {
    int carry = 0;
    for (size_t i=0; i<a.size() || carry; ++i) {
        if (i == a.size())
            a.push_back (0);
        long long cur = carry + a[i] * 1ll * b;
        a[i] = int (cur % base);
        carry = int (cur / base);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();
}

// Multiplication by long integer
vi operation*(vi& a, vi& b) {
    vi c(a.size()+b.size());
    for (size_t i=0; i<a.size(); ++i)
        for (int j=0, carry=0; j<(int)b.size() || carry; ++j) {
            long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
            c[i+j] = int (cur % base);
            carry = int (cur / base);
        }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
}

// Division by short integer b < base
void operation/=(vi& a, vi& b) {
    int carry = 0;
    for (int i=(int)a.size()-1; i>=0; --i) {
        long long cur = a[i] + carry * 1ll * base;
        a[i] = int (cur / b);
        carry = int (cur % b);
    }
    while (a.size() > 1 && a.back() == 0)
        a.pop_back();?
}