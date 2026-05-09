struct SegmentTree{
    struct Node{
        int sum, f, d, len;
    } tree[MAXN << 2];
    void pull(int id){
        tree[id].sum = tree[id << 1].sum + tree[id << 1 | 1].sum;
    }
    void addtag(int id, int a, int d){
        tree[id].f += a;
        tree[id].d += d;
        tree[id].sum += (2 * a + (tree[id].len - 1) * d) * tree[id].len / 2;
    }
    void push(int id){
        if(!tree[id].f && !tree[id].d) return;
        int mid_f = tree[id].f + tree[id << 1].len * tree[id].d;
        addtag(id << 1, tree[id].f, tree[id].d);
        addtag(id << 1 | 1, mid_f, tree[id].d);
        tree[id].f = tree[id].d = 0;
    }
    void build(int l, int r, int id, int ar[]){
        tree[id].len = r - l + 1;
        tree[id].f = tree[id].d = 0;
        if(l == r){
            tree[id].sum = ar[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, id << 1, ar);
        build(mid + 1, r, id << 1 | 1, ar);
        pull(id);
    }
    void update(int ql, int qr, int a, int d, int l, int r, int id){
        if(ql <= l and r <= qr){
            addtag(id, a + (l - ql) * d, d);
            return;
        }
        push(id);
        int mid = (l + r) >> 1;
        if(ql <= mid) update(ql, qr, a, d, l, mid, id << 1);
        if(qr > mid) update(ql, qr, a, d, mid + 1, r, id << 1 | 1);
        pull(id);
    }
    int query(int ql, int qr, int l, int r, int id){
        if(ql <= l and r <= qr) return tree[id].sum;
        push(id);
        int mid = (l + r) >> 1, re = 0;
        if(ql <= mid) re += query(ql, qr, l, mid, id << 1);
        if(qr > mid) re += query(ql, qr, mid + 1, r, id << 1 | 1);
        return re;
    }
};