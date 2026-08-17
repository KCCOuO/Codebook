/*
dp(l,r) = min l≤k<r {dp(l, k) + dp(k + 1,r) + w(l,r)} l ≤ r
dp(l,r) = min l≤k<r {dp(l, k) + w(k + 1,r)} l ≤ r
以上暴力做會是 O(n^3)，若 w 滿足四邊形不等式以及區間單調
性，總體時間複雜度可壓到 O(n^2)。
區間單調性
∀a, b, c, d, a ≤ b ≤ c ≤ d, w(a, d) ≥ w(b, c)

若 w 滿足四邊形不等式以及區間單調性，那麼這個 DP 也
滿足四邊形不等式。

如果 2D/1D DP 滿足四邊形不等式，令 p(l,r) 代表 dp(l,r)
的最優決策點，則有 p(l,r − 1) ≤ p(l,r) ≤ p(l + 1,r)

*/
vector<vector<ll>> dp(n, vector<ll>(n, inf));
vector<vector<int>> p(n, vector<int>(n));
ll w(int l, int r) {} // [l, r]
for (int len = 0; len < n; len++) {
    for (int i = 0; i + len < n; i++) {
        int j = i + len;
        if (i == j) {
            dp[i][j] = 0, p[i][j] = i;
            continue;
        }
        for (int k = p[i][j - 1]; k <= min(p[i + 1][j], j - 1); k++) {
            ll x = dp[i][k] + dp[k + 1][j] + w(i, j);
            if (x < dp[i][j]) dp[i][j] = x, p[i][j] = k;
        }
    }
}