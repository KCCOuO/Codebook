struct Node{
    int sum = 0;
    Node *l = nullptr;
    Node *r = nullptr;
}*root = nullptr;
 
void add(Node *&node, int L, int R, int pos, int val)
{
    if(!node) node = new Node();
    node->sum += val;
    if(L == R) return;
    int mid = (L + R) / 2;
    if(pos <= mid) add(node->l, L, mid, pos, val);
    else add(node->r, mid + 1, R, pos, val);
}
int query(Node *node, int L, int R, int ql, int qr)
{
    if(!node) return 0;
    if(ql <= L and R <= qr) return node->sum;
    int mid = (L + R) / 2, ans = 0;
    if(ql <= mid) ans += query(node->l, L, mid, ql, qr);
    if(qr > mid) ans += query(node->r, mid + 1, R, ql, qr);
    return ans;
}