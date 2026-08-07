struct Line{
    int k, b;
    int val(int x){
        return k * x + b;
    }
};
Line tree[(int)1e6]; //維護最大值
bool has_line[(int)1e6];
void insert(int node, int l, int r, Line new_line)
{
    if(!has_line[node]){
        tree[node] = new_line;
        has_line[node] = true;
        return;
    }
    int mid = (l + r) >> 1;
    bool l_better = new_line.val(l) > tree[node].val(l);
    bool mid_better = new_line.val(mid) > tree[node].val(mid);
    if(mid_better) swap(new_line, tree[node]);
    if(l == r) return;
    if(l_better != mid_better) insert(node << 1, l, mid, new_line);
    else insert(node << 1 | 1, mid + 1, r, new_line);
}
int query(int node, int l, int r, int x)
{
    if(!has_line[node]) return -2e18;
    int re = tree[node].val(x);
    if(l == r) return re;
    int mid = (l + r) >> 1;
    if(x <= mid) re = max(re, query(node << 1, l, mid, x));
    else re = max(re, query(node << 1 | 1, mid + 1, r, x));
    return re;
}