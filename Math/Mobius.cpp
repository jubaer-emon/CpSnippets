vector<ll> mu;

void mobius (int lim) {
    mu = vector<ll>(lim);
    vector<int> primes;
    vector<int> lp(lim, 0); // lowest prime factor
    mu[1] = 1;

    for (int i = 2; i < lim; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1; // prime → μ(p) = -1
        }

        for (int p : primes) {
            if (p > lp[i] || 1LL * p * i > lim) break;

            lp[p * i] = p;

            if (p == lp[i]) {
                // p divides i → p^2 divides p*i → μ = 0
                mu[p * i] = 0;
                break;
            } else {
                // square-free, one more prime factor → multiply by -1
                mu[p * i] = -mu[i];
            }
        }
    }
}