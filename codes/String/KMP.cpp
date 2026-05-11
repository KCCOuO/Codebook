vector<int> pi(s.size(), 0);
for(int i = 1, j = 0; i < s.size(); i++){
    while(j > 0 and s[i] != s[j]) j = pi[j - 1];
    if(s[i] == s[j]) j++;
    pi[i] = j;
}