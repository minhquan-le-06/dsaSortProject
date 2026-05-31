#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    // Tối ưu 1: Chia xô tĩnh, tránh cấp phát động liên tục
    vector<string> buckets[105];
    string s;
    
    // Tối ưu 2: Dùng reserve() nếu đoán trước được kích thước xô, nhưng do n <= 10^4 nên không bắt buộc.
    for (int i = 0; i < n; ++i) {
        cin >> s;
        // Tối ưu 3: Move semantics, cướp luôn vùng nhớ thay vì copy string tốn O(L)
        buckets[s.length()].push_back(move(s)); 
    }
    
    cout << n << "\n";
    
    // Tối ưu 4: Chỉ sort từng phần nhỏ (Divide and Conquer) và loại bỏ bước kiểm tra độ dài.
    for (int len = 10; len <= 100; ++len) {
        if (!buckets[len].empty()) {
            sort(buckets[len].begin(), buckets[len].end());
            for (const string& str : buckets[len]) {
                cout << str << "\n";
            }
        }
    }
    return 0;
}
