// 用有向線段 AB 切割多邊形 v，保留左半邊
vector<point> cut(vector<point> v, point a, point b)
{
    vector<point> ans;
    int n = v.size();
    
    for(int i = 0; i < n; i++){
        point c = v[i], d = v[(i + 1) % n];

        double side_c = cross(b - a, c - a);
        double side_d = cross(b - a, d - a);
        if(side_c >= 0){
            ans.pb(c);
            if(side_d < 0) ans.pb(intersect(a, b, c, d));
        }
        else{
            if(side_d >= 0) ans.pb(intersect(a, b, c, d));
        }
    }
    return ans;
}