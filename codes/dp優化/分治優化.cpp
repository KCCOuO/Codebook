/*
dp(i) = h(i) + min/max j<i {dp(j) + w(j, i)}
其中 w(j, i) 必須滿足四邊形不等式。
四邊形不等式
對於任意 a ≤ b ≤ c ≤ d，若滿足
w(a, c) + w(b, d) ≤ (≥) w(a, d) + w(b, c)
則稱 w 滿足四邊形不等式。
*/
ll w(int l, int r) {} // (l, r]
void solve(int j, int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r) / 2;
    dp[j][m] = INF;
    int optm = -1;
    for (int p = optl; p <= min(m - 1, optr); p++) {
        ll val = dp[j - 1][p] + w(p, m);
        if (val < dp[j][m]) {
            dp[j][m] = val;
            optm = p;
        }
    }
    solve(j, l, m - 1, optl, optm);
    solve(j, m + 1, r, optm, optr);
}