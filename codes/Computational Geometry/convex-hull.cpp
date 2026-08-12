double cross(point a, point b) {return a.x * b.y - a.y * b.x;}
vector<point> build(vector<point> v)
{
    vector<point> ans;
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size(); i++){
        while(ans.size() > 1 and cross(ans.end()[-2] - ans.end()[-1], ans.end()[-2] - v[i]) > 0) ans.pop_back();
        ans.pb(v[i]);
    }
    for(int i = v.size() - 2; i >= 0; i--){
        while(ans.size() > 1 and cross(ans.end()[-2] - ans.end()[-1], ans.end()[-2] - v[i]) > 0) ans.pop_back();
        ans.pb(v[i]);
    }
    ans.pop_back();
    return ans;
}