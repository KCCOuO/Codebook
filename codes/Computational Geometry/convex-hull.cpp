struct node{
    int x, y;
    node operator - (const node &b) {
        return {x - b.x, y - b.y};
    }
    int operator * (const node &b) {
        return x * b.y - y * b.x;
    }
    bool operator < (const node &b) {
        if (x != b.x) return x < b.x;
        return y < b.y;
    }
};
vector<node> build(vector<node> v)
{
    vector<node> ans;
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        while(ans.size() > 1 and (ans.end()[-2] - ans.end()[-1]) * (ans.end()[-2] - v[i]) > 0){
            ans.pop_back();
        }
        ans.pb(v[i]);
    }
    for(int i = v.size() - 2; i >= 0; i--){
        while(ans.size() > 1 and (ans.end()[-2] - ans.end()[-1]) * (ans.end()[-2] - v[i]) > 0){
            ans.pop_back();
        }
        ans.pb(v[i]);
    }
    ans.pop_back();
    return ans;
}