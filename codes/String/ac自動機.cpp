int trie[(int)5e5 + 5][26], node_cnt = 0, fail[(int)5e5 + 5]; // ac_automachine
int pattern_end[(int)5e5 + 5];
void insert(string s, int id)
{
    int u = 0;
    for(char c : s){
        int v = c - 'a';
        if(!trie[u][v]) trie[u][v] = ++node_cnt;
        u = trie[u][v];
    }
    pattern_end[id] = u;
}
void build_ac_automachine()
{
    //bfs
    queue<int> q;
    for(int i = 0; i < 26; i++) if(trie[0][i] > 0) q.push(trie[0][i]);
    while(q.size()){
        int x = q.front(); q.pop();
        for(int i = 0; i < 26; i++){
            if(trie[x][i] > 0){
                fail[trie[x][i]] = trie[fail[x]][i];
                q.push(trie[x][i]);
            }
            else trie[x][i] = trie[fail[x]][i];
        }
    }
}