using cd = complex<double>;

const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();

    // Bit reversal
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;

        for(; j & bit; bit >>= 1) j ^= bit;

        j ^= bit;
    
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));

        for(int i = 0; i < n; i += len){
            cd w(1);

            for(int j = 0; j < len / 2; j++){
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;

                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;

                w *= wlen;
            }
        }
    }

    if(invert){
        for(cd& x : a) x /= n;
    }
}
// (a[0] + a[1]x + a[2]x^2 + ...) * (b[0] + b[1]x + b[2]x^2 + ...)
vector<long long> multiply(vector<long long> a, vector<long long> b) {
    int n = 1;

    while(n < a.size() + b.size()) n <<= 1;

    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for(int i = 0; i < n; i++) fa[i] *= fb[i];

    fft(fa, true);

    vector<long long> res(n);

    for(int i = 0; i < n; i++) res[i] = llround(fa[i].real());

    return res;
}