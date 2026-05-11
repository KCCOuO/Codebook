string s, t = "^";
cin >> s;
for(char c : s){
    t += "#";
    t += c;
}
t += "##";
vector<int> p(t.size(), 0);
int c = 0, r = 0, len = 0, center = 0;
for(int i = 1; i < t.size() - 1; i++){
    if(i < r) p[i] = min(r - i, p[2 * c - i]);
    while(t[i + p[i] + 1] == t[i - p[i] - 1]) p[i]++;
    if(i + p[i] > r){
        r = i + p[i];
        c = i;
    }
    if(p[i] > len){
        len = p[i];
        center = i;
    }
}
cout << s.substr((center - len) / 2, len) << "\n"; //Longest Palindrome