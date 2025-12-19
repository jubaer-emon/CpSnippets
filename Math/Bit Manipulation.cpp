#pragma GCC target("popcnt")

ll set(ll n, ll i) {
    return n | (1<<i);
}

ll flip(ll n, ll i) {
    return n ^ (1<<i);
}

ll clear(ll n, ll i) {
    return n & ~(1<<i);
}

bool isSet(ll n, ll i) {
    return (n >> i) & 1;
}

ll clearRightMostSetBit(ll n) {
    return n & (n-1);
}

void printBinary(ll n) {
    cout << bitset<10>(n) << endl; // can use .to_string()
}

ll toDecimal(string& bin) {
    return bitset<10>(bin).to_ullong();
}

ll popcount(ll x) {
    return __builtin_popcountll(x);
}

ll countLeadingZeros(ll x) {
    return __builtin_clzll(x);
}

ll countTrailingZeros(ll x) {
    return __builtin_ctzll(x);
}

ll firstSetBit(ll x) {
    return __builtin_ffsll(x);
}

// is no of set bits odd
ll parity(ll x) {
    return __builtin_partiyll(x);
}