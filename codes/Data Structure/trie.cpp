struct Node{
    int next_node[2]; // 01-trie
    int max_idx;
    Node() {
        next_node[0] = next_node[1] = -1;
        max_idx = -1;
    }
};
vector<Node> trie;
void init_trie()
{
    trie.clear();
    trie.emplace_back(); // 插入根節點
}
void insert(int x, int id)
{
    int u = 0;
    for(int i = 29; i >= 0; i--){
        int bit = (x >> i) & 1;
        if(trie[u].next_node[bit] == -1){
            trie[u].next_node[bit] = trie.size();
            trie.emplace_back();
        }
        u = trie[u].next_node[bit];
        trie[u].max_idx = max(trie[u].max_idx, id);
    }
}