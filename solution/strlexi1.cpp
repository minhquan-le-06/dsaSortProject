#include <iostream>
#include <vector>
#include <string>

using namespace std;

inline int charAt(const string &s, int d) {
    if (d < (int)s.size()) 
        return (unsigned char)s[d];
    return -1;
}

void swapStr(string &a, string &b) {
    string t = a;
    a = b;
    b = t;
}

void insertionSort(vector<string> &a, int lo, int hi, int d) {
    for (int i = lo + 1; i <= hi; i++) {
        for (int j = i; j > lo && a[j].compare(d, string::npos, a[j-1], d, string::npos) < 0; j--)
            swap(a[j], a[j-1]);
    }
}




void quicksort(vector<string> &a, int lo, int hi, int d) {
    if (hi - lo < 20) {
        insertionSort(a, lo, hi, d);
        return;
    }

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);

        if (t < v) {
            swapStr(a[lt++], a[i++]);
        } else if (t > v) {
            swapStr(a[i], a[gt--]);
        } else {
            i++;
        }
    }

    quicksort(a, lo, lt - 1, d);
    if (v >= 0) 
        quicksort(a, lt, gt, d + 1);
    quicksort(a, gt + 1, hi, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    quicksort(a, 0, n - 1, 0);

    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}