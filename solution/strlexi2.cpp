#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 100005;
char* str_ptrs[MAXN];
char* temp_ptrs[MAXN];

char in_buf[15000005]; 
char out_buf[15000005];

const int INSERTION_THRESHOLD = 48; 

inline void insertion_sort(char** a, int n, int depth) {
    for (int i = 1; i < n; ++i) {
        char* tmp = a[i];
        int j = i;
        for (; j > 0; --j) {
            char* prev = a[j - 1];
            int d = depth;
            while (prev[d] == tmp[d] && prev[d] != '\0') d++;
            if (prev[d] <= tmp[d]) break;
            a[j] = prev;
        }
        a[j] = tmp;
    }
}

void msd_radix_sort(char** a, char** tmp, int n, int depth) {
    if (n <= INSERTION_THRESHOLD) {
        insertion_sort(a, n, depth);
        return;
    }

    int count[28] = {0};
    
    for (int i = 0; i < n; ++i) {
        int c = a[i][depth];
        count[c ? c - 96 : 0]++;
    }

    int pos[28];
    pos[0] = 0;
    for (int i = 1; i < 28; ++i) {
        pos[i] = pos[i - 1] + count[i - 1];
    }

    int cur[28];
    memcpy(cur, pos, sizeof(pos));

    for (int i = 0; i < n; ++i) {
        int c = a[i][depth];
        tmp[cur[c ? c - 96 : 0]++] = a[i];
    }

    memcpy(a, tmp, n * sizeof(char*));

    for (int i = 1; i < 27; ++i) {
        if (count[i] > 1) {
            msd_radix_sort(a + pos[i], tmp + pos[i], count[i], depth + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t len = fread(in_buf, 1, sizeof(in_buf), stdin);
    in_buf[len] = '\0';
    
    int n = 0;
    char* p = in_buf;
    
    // Parse N
    while (*p && (*p < '0' || *p > '9')) p++;
    while (*p >= '0' && *p <= '9') {
        n = n * 10 + (*p - '0');
        p++;
    }
    
    int count = 0;
    while (count < n && *p) {
        while (*p && (*p < 'a' || *p > 'z')) p++;
        if (!*p) break;
        
        str_ptrs[count++] = p;
        
        while (*p >= 'a' && *p <= 'z') p++;
        *p = '\0'; 
        p++;
    }
    n = count;
    
    msd_radix_sort(str_ptrs, temp_ptrs, n, 0);
    
    char* op = out_buf;
    
    int temp_n = n;
    char num_buf[15];
    int num_len = 0;
    if (temp_n == 0) num_buf[num_len++] = '0';
    while (temp_n > 0) {
        num_buf[num_len++] = static_cast<char>((temp_n % 10) + '0');
        temp_n /= 10;
    }
    for (int i = num_len - 1; i >= 0; i--) {
        *op++ = num_buf[i];
    }
    *op++ = '\n';
    
    for (int i = 0; i < n; i++) {
        char* s = str_ptrs[i];
        while (*s) {
            *op++ = *s++;
        }
        *op++ = '\n';
    }
    
    fwrite(out_buf, 1, op - out_buf, stdout);
    
    return 0;
}
