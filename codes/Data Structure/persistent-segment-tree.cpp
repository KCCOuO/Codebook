int upd(int pre, int l, int r, int pos, int val)
{
    int node = ++cnt_tree;
    tree[node] = tree[pre];
    if(l == r){
        tree[node].sum += val;
        return node;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) tree[node].l = upd(tree[pre].l, l, mid, pos, val);
    else tree[node].r = upd(tree[pre].r, mid + 1, r, pos, val);
    tree[node].sum = tree[tree[node].l].sum + tree[tree[node].r].sum;
    return node;
}
int query(int node, int l, int r, int ql, int qr)
{
    if(ql <= l and r <= qr) return tree[node].sum;
    int mid = (l + r) >> 1, re = 0;
    if(ql <= mid) re += query(tree[node].l, l, mid, ql, qr);
    if(qr > mid) re += query(tree[node].r, mid + 1, r, ql, qr);
    return re;
}
int get_kth(int node_l, int node_r, int l, int r, int k)
{
    // 區間第k小
    /*
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int left_cnt = tree[tree[node_r].l].sum - tree[tree[node_l].l].sum;
    if(k <= left_cnt) return get_kth(tree[node_l].l, tree[node_r].l, l, mid, k);
    else return get_kth(tree[node_l].r, tree[node_r].r, mid + 1, r, k - left_cnt);
    */
    while (l < r) {
        int mid = (l + r) >> 1;
        int left_cnt = tree[tree[node_r].l].sum - tree[tree[node_l].l].sum;
        if (k <= left_cnt) {
            node_l = tree[node_l].l;
            node_r = tree[node_r].l;
            r = mid;
        } else {
            k -= left_cnt;
            node_l = tree[node_l].r;
            node_r = tree[node_r].r;
            l = mid + 1;
        }
    }
    return l;
}