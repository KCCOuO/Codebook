vector<int> buildSuffixArray(string s, int n)
{
    vector<int> sa(n), tmp(n), rank(n);
    /*
    sa[i]: 從sa[i]開始的後綴字串是第i小
    rank[i]: 從i開始的後綴字串是第幾小
    tmp: rank的暫存
    */
    for(int i = 0; i < n; i++){ // 初始化長度為1的後綴字串
        sa[i] = i;
        rank[i] = s[i] - 'a';
    }
    for(int k = 1; k < n; k <<= 1){
        auto cmp = [&](int i, int j){ //比較長度為2*k的字串
            if(rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = i + k < n ? rank[i + k] : -1;
            int rj = j + k < n ? rank[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp); //sa 按照字典序(rank)排列
        /*
        更新rank
        要先用tmp存，因為cmp會用到rank的舊資料
        */
        tmp[sa[0]] = 0;
        for(int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rank = tmp;
    }
    return sa;
}
vector<int> buildLCP(string s, vector<int> sa, int n)
{
    vector<int> rank(n, 0); // rank[i]: 從s[i]開始的字尾字串按照字典序排序後的位置
    for(int i = 0; i < n; i++) rank[sa[i]] = i;
    int h = 0;// 因為是按字串s原始位置順序計算，用前綴相似的特性，h每次最多只會減少1
    vector<int> lcp(n, 0); // 與字典序前一個的字尾字串的最長共同前綴長度
    for(int i = 0; i < n; i++){
        if(rank[i] > 0){
            int j = sa[rank[i] - 1]; // 字典序前一個的字尾字串
            while(i + h < n and j + h < n and s[i + h] == s[j + h]) h++;
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}
int ans = 0, n = s.size();
// ans: the number of distinct substrings that appear in a string
for(int i = 0; i < n; i++) ans += n - sa[i] - lcp[i];
/*
(n - sa[i])：這個字尾本來可以貢獻這麼多個子字串。
lcp[i]：扣掉跟字典序前一個字尾長得一模一樣的前綴，因為那些已經算過了。
*/