vector<int> ZValue(const string &s) {
    vector<int> z(s.length(), 0);
    for (int i = 1, l = 1, r = 1; i < (int) s.length(); i++) {
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < (int) s.length() && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }
        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}