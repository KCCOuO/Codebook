#include<bits/stdc++.h>
using namespace std;
int main() {
    // 1. 在迴圈外編譯，並檢查是否成功
    cout << "Compiling files..." << endl;
    
    // system() 回傳 0 代表成功執行
    int c1 = system("g++ -Wall -std=c++20 sol.cpp -o sol.exe");
    int c2 = system("g++ -Wall -std=c++20 bf.cpp -o bf.exe");
    int c3 = system("g++ -Wall -std=c++20 gen.cpp -o gen.exe");

    if (c1 != 0 || c2 != 0 || c3 != 0) {
        cout << "Compilation Failed! Check if sol.cpp, bf.cpp, and gen.cpp exist." << endl;
        return 1;
    }

    cout << "Compilation successful. Starting stress test..." << endl;
    
    for (int T = 1; ; T++) {
        // 2. 執行程序
        system("gen.exe > input.txt");
        system("sol.exe < input.txt > sol.out");
        system("bf.exe < input.txt > bf.out");
        
        // 3. 使用 fc /W 比對
        if (system("fc sol.out bf.out > nul")) {
            system("fc sol.out bf.out");
            cout << "WA on Test #" << T << "!" << endl;
            // 發生錯誤時停止，此時 input.txt 就是出錯的測資
            break;
        } else {
            if (T % 10 == 0) cout << "Passed " << T << " tests..." << endl;
        }
    }
    return 0;
}