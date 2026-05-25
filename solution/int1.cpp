#include <iostream>
#include <vector>
using namespace std;

static const int MASK = 65535;
static const int BASE = 65536;

void radix_sort(vector<int>& a) {
    int n = (int)a.size();

    vector<int> b(n);

    int *in = a.data();
    int *out = b.data();

    for (int pass = 0; pass < 2; pass++) {
        int shift = pass * 16;

        int count[BASE] = {0};

        for (int i = 0; i < n; i++) {
            unsigned int x = (unsigned int)in[i] ^ 0x80000000;
            int digit = (x >> shift) & MASK;
            count[digit]++;
        }

        for (int i = 1; i < BASE; i++) {
            count[i] += count[i - 1];
        }


        for (int i = n - 1; i >= 0; i--) {
            unsigned int x = (unsigned int)in[i] ^ 0x80000000;
            int digit = (x >> shift) & MASK;
            out[--count[digit]] = in[i];
        }

        int* tmp = in;
        in = out;
        out = tmp;
    }

    if (in != a.data()) {
        for (int i = 0; i < n; i++) {
            a[i] = in[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    radix_sort(a);

    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        cout << a[i] << '\n';
    }

    return 0;
}