//1. Order matters + unlimited repetition
for (int x = 0; x <= target; x++)          // sum first
    for (int c : coins)                    // then coins
        if (x >= c)
            dp[x] += dp[x - c];

// 2. Order matters + no repetition
for (int x = target; x >= 0; x--)          // sum backward
    for (int c : coins)                    // coins inner
        if (x >= c)
            dp[x] += dp[x - c];

// 3. Order doesn't matter + unlimited repetition
// STANDARD COIN CHANGE
for (int c : coins)                        // coins first
    for (int x = c; x <= target; x++)      // then sum
        dp[x] += dp[x - c];

// 4. Order doesn't matter + no repetition
// 0-1 KNAPSACK style
for (int c : coins)                        // coins first
    for (int x = target; x >= c; x--)      // sum backward
        dp[x] += dp[x - c];

// Binary Splitting (large k)
for (int i = 0; i < m; i++) {
    int c = coins[i];
    int k = cnt[i];

    // decompose k into sums of powers of 2
    int t = 1;
    while (k > 0) {
        int use = min(t, k);
        int weight = use * c;

        // 0/1 knapsack update
        for (int x = target; x >= weight; x--) {
            dp[x] += dp[x - weight];
        }

        k -= use;
        t <<= 1;
    }
}

