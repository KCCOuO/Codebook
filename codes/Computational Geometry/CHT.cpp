// 當放入的直線斜率單調遞增(or遞減)可以使用deque
// 否則用李超樹
struct Line
{
    int m, b;
    int val(int x){
        return m * x + b;
    }
};
bool bad(Line a, Line b, Line c)
{
    // ab交點x座標 >= bc交點x座標
    // (b.b - a.b) / (a.m - b.m) >= (c.b - b.b) / (b.m - c.m)
    return (b.b - a.b) * (b.m - c.m) >= (c.b - b.b) * (a.m - b.m);
}
deque<Line> dq;
dq.pb({x, 0});
for(int i = 1; i <= n; i++){
    while(dq.size() > 1 and dq[0].val(s[i]) >= dq[1].val(s[i])) dq.pop_front();
    dp[i] = dq[0].val(s[i]);
    Line tmp = {f[i], dp[i]};
    while(dq.size() >= 2 and bad(dq[dq.size() - 2], dq.back(), tmp)) dq.pop_back();
    dq.pb(tmp);
}
