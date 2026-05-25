#include <iostream>
#include <cstdio>

using namespace std;

const int BUF_SIZE = 1 << 20;
char in_buf[BUF_SIZE];
int buf_pos = 0;
int buf_len = 0;

inline char getChar() {
    if (buf_pos == buf_len) {
        buf_len = fread(in_buf, 1, BUF_SIZE, stdin);
        buf_pos = 0;
        if (buf_len == 0) return EOF;
    }
    return in_buf[buf_pos++];
}

inline int readInt() {
    int x = 0, f = 1;
    char ch = getChar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        if (ch == EOF) return 0;
        ch = getChar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getChar();
    }
    return x * f;
}

char out_buf[BUF_SIZE];
int out_pos = 0;

inline void flushOut() {
    if (out_pos) {
        fwrite(out_buf, 1, out_pos, stdout);
        out_pos = 0;
    }
}

inline void putChar(char ch) {
    if (out_pos == BUF_SIZE) flushOut();
    out_buf[out_pos++] = ch;
}

inline void writeInt(int x) {
    if (x < 0) {
        putChar('-');
        x = -x;
    }
    if (x == 0) {
        putChar('0');
        return;
    }
    char s[12];
    int len = 0;
    while (x > 0) {
        s[len++] = (x % 10) + '0';
        x /= 10;
    }
    while (len--) putChar(s[len]);
}

int count0[65536];
int count1[65536];

int main() {
    int n = readInt();
    if (n <= 0) {
        if (n == 0) { writeInt(0); putChar('\n'); flushOut(); }
        return 0;
    }

    unsigned int* data = new unsigned int[n];
    unsigned int* temp = new unsigned int[n];

    for (int i = 0; i < n; i++) {
        unsigned int val = (unsigned int)readInt() ^ 0x80000000;
        data[i] = val;
        count0[val & 0xFFFF]++;
        count1[val >> 16]++;
    }

    for (int i = 1; i < 65536; i++) {
        count0[i] += count0[i - 1];
        count1[i] += count1[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        temp[--count0[data[i] & 0xFFFF]] = data[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        data[--count1[temp[i] >> 16]] = temp[i];
    }

    writeInt(n);
    putChar('\n');
    for (int i = 0; i < n; i++) {
        writeInt((int)(data[i] ^ 0x80000000));
        putChar('\n');
    }

    flushOut();
    
    delete[] data;
    delete[] temp;
    return 0;
}