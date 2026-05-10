#include<bits/stdc++.h>
using namespace std;

// 使用隨機種子，確保每次生成的數據都不同
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// 生成 [l, r] 範圍內的隨機整數
long long rnd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

// 生成一棵隨機樹 (N 個點，N-1 條邊)
void gen_tree(int n) {
    for (int i = 2; i <= n; i++) {
        // 讓每個點 i 連向 [1, i-1] 中的隨機點
        int u = i;
        int v = rnd(1, i - 1);
        cout << u << " " << v << "\n";
    }
}