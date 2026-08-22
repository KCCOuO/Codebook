struct Line{
    int k, b;
    int val(int x){
        return k * x + b;
    }
};
struct Node{
    Node *l = nullptr;
    Node *r = nullptr;
    bool has_line = false;
    Line line;
} *root = nullptr; //維護最大值
void insert(Node *&node, int l, int r, Line new_line)
{
    if(!node) node = new Node();
    if(!node->has_line){
        node->line = new_line;
        node->has_line = true;
        return;
    }
    int mid = (l + r) >> 1;
    bool l_better = new_line.val(l) > node->line.val(l);
    bool mid_better = new_line.val(mid) > node->line.val(mid);
    if(mid_better) swap(new_line, node->line);
    if(l == r) return;
    if(l_better != mid_better) insert(node->l, l, mid, new_line);
    else insert(node->r, mid + 1, r, new_line);
}
int query(Node *node, int l, int r, int x)
{
    if(!node) return -2e18;
    if(!node->has_line) return -2e18;
    int re = node->line.val(x);
    if(l == r) return re;
    int mid = (l + r) >> 1;
    if(x <= mid) re = max(re, query(node->l, l, mid, x));
    else re = max(re, query(node->r, mid + 1, r, x));
    return re;
}