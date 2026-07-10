const int a = 31;
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;
struct BIT{
    int n;
    vector<int> bit1, bit2;
    BIT(int _n){
        n = _n;
        bit1.resize(n + 1, 0);
        bit2.resize(n + 1, 0);
    }
    void add(int x, int val1, int val2){
        int y = x;
        for(; x <= n; x += x & -x) bit1[x] = (bit1[x] + val1) % mod1;
        for(; y <= n; y += y & -y) bit2[y] = (bit2[y] + val2) % mod2;
    }
    int que1(int x){
        int ans = 0;
        for(; x; x -= x & -x) ans = (ans + bit1[x]) % mod1;
        return ans;
    }
    int que2(int x){
        int ans = 0;
        for(; x; x -= x & -x) ans = (ans + bit2[x]) % mod2;
        return ans;
    }
    int query1(int l, int r){
        return (que1(r) - que1(l - 1) + mod1) % mod1;
    }
    int query2(int l, int r){
        return (que2(r) - que2(l - 1) + mod2) % mod2;
    }
};
void solve()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<int> f1(n, 1), f2(n, 1);
    BIT bit(n);
    for(int i = 1; i < n; i++) f1[i] = (f1[i - 1] * a) % mod1;
    for(int i = 1; i < n; i++) f2[i] = (f2[i - 1] * a) % mod2;
    for(int i = 0; i < n; i++) bit.add(i + 1, f1[i] * (s[i] - 'a' + 1) % mod1, f2[i] * (s[i] - 'a' + 1) % mod2);
    set<pii> cnt;
    for(int i = k; i <= n; i++){
        int sum1 = bit.query1(i - k + 1, i) * fpow(f1[i - k], mod1 - 2, mod1) % mod1;
        int sum2 = bit.query2(i - k + 1, i) * fpow(f2[i - k], mod2 - 2, mod2) % mod2;
        cnt.insert({sum1, sum2});
    }
    cout << cnt.size() << "\n";
}