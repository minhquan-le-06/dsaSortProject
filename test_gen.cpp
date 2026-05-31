#include "main.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

// STRLENLEXI

const string PREFIX_LEN = string(96, 'a');

string get_suffix_len(int val) {
    string s = "aaaa";
    for (int i = 3; i >= 0; --i) {
        s[i] = 'a' + (val % 26);
        val /= 26;
    }
    return s;
}

void gen_strlenlexi() {
    int n = 10000;
    
    ofstream f1("strlenlexi/test001.in");
    f1 << n << "\n";
    for (int i = n - 1; i >= 0; --i) f1 << PREFIX_LEN + get_suffix_len(i) << "\n";

    ofstream f2("strlenlexi/test002.in");
    f2 << n << "\n";
    int left = 0, right = n - 1;
    while (left <= right) {
        f2 << PREFIX_LEN + get_suffix_len(left++) << "\n";
        if (left <= right) f2 << PREFIX_LEN + get_suffix_len(right--) << "\n";
    }

    ofstream f3("strlenlexi/test003.in");
    f3 << n << "\n";
    vector<string> arr3(n);
    mt19937 rng3(1234);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) arr3[i] = string(100, 'a');
        else arr3[i] = string(99, 'a') + "b";
    }
    shuffle(arr3.begin(), arr3.end(), rng3);
    for (const string& s : arr3) f3 << s << "\n";

    ofstream f4("strlenlexi/test004.in");
    f4 << n << "\n";
    vector<string> arr4(n);
    for (int i = 0; i < n; ++i) arr4[i] = PREFIX_LEN + get_suffix_len(i);
    vector<string> pipe;
    pipe.reserve(n);
    for (int i = 0; i < n; i += 2) pipe.push_back(arr4[i]);
    for (int i = n - 1 - (n % 2 == 0 ? 0 : 1); i >= 0; i -= 2) pipe.push_back(arr4[i]);
    for (const string& s : pipe) f4 << s << "\n";

    ofstream f5("strlenlexi/test005.in");
    f5 << n << "\n";
    for (int i = 0; i < n; ++i) {
        string s = "";
        int val = i;
        for(int j = 0; j < 100; ++j) {
            s += (val % 2 == 0) ? 'a' : 'b';
            val /= 2;
        }
        f5 << s << "\n";
    }
}

// INT 
void gen_int() {
    int N = 100000;
    long long MIN_VAL = -2147483648LL;
    long long MAX_VAL = 2147483647LL;
    mt19937 rng(42);

    ofstream f1("int/test001.in");
    f1 << N << "\n";
    for (int i = 0; i < N; ++i) f1 << MAX_VAL - i << "\n";

    ofstream f2("int/test002.in");
    f2 << N << "\n";
    for (int i = 0; i < N; ++i) f2 << 424242 << "\n";

    ofstream f3("int/test003.in");
    f3 << N << "\n";
    uniform_int_distribution<long long> dist(MIN_VAL, MAX_VAL);
    for (int i = 0; i < N; ++i) f3 << dist(rng) << "\n";

    ofstream f4("int/test004.in");
    f4 << N << "\n";
    uniform_int_distribution<int> small_dist(0, 100);
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) f4 << MIN_VAL + small_dist(rng) << "\n";
        else f4 << MAX_VAL - small_dist(rng) << "\n";
    }

    ofstream f5("int/test005.in");
    f5 << N << "\n";
    long long options[3] = {MIN_VAL, 0, MAX_VAL};
    uniform_int_distribution<int> opt_dist(0, 2);
    for (int i = 0; i < N; ++i) f5 << options[opt_dist(rng)] << "\n";
}

// STRLEXI 
string to_base26(int num, int length = 5) {
    string res = "";
    for (int i = 0; i < length; ++i) {
        res += (char)((num % 26) + 'a');
        num /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
}

void gen_strlexi() {
    int N = 100000;
    mt19937 rng(42);

    ofstream f1("strlexi/test001.in");
    f1 << N << "\n";
    uniform_int_distribution<int> char_dist(0, 25);
    for (int i = 0; i < N; ++i) {
        string s = "";
        for (int j = 0; j < 100; ++j) s += (char)('a' + char_dist(rng));
        f1 << s << "\n";
    }

    ofstream f2("strlexi/test002.in");
    f2 << N << "\n";
    string prefix95(95, 'a');
    vector<string> data2(N);
    for (int i = 0; i < N; ++i) {
        data2[i] = prefix95 + to_base26(i, 5);
        f2 << data2[i] << "\n";
    }

    ofstream f3("strlexi/test003.in");
    f3 << N << "\n";
    for (int i = N - 1; i >= 0; --i) f3 << data2[i] << "\n";

    ofstream f4("strlexi/test004.in");
    f4 << N << "\n";
    string z100(100, 'z');
    for (int i = 0; i < N; ++i) f4 << z100 << "\n";

    ofstream f5("strlexi/test005.in");
    f5 << N << "\n";
    string s_even = "aa" + string(98, 'a');
    string s_odd = "aa" + string(8, 'b');
    for (int i = 0; i < N; ++i) {
        if (i % 2 == 0) f5 << s_even << "\n";
        else f5 << s_odd << "\n";
    }
}


int main() {
    #ifdef _WIN32
        system("mkdir strlenlexi 2> NUL");
        system("mkdir int 2> NUL");
        system("mkdir strlexi 2> NUL");
    #else
        system("mkdir -p strlenlexi 2> /dev/null");
        system("mkdir -p int 2> /dev/null");
        system("mkdir -p strlexi 2> /dev/null");
    #endif

    gen_strlenlexi();
    
    gen_int();
    
    gen_strlexi();

    cout << "\n15 file test case cho 3 bai." << endl;
    return 0;
}
