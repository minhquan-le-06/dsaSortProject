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
    
    vector<string> buckets[105];
    string s;
    
    for (int i = 0; i < n; ++i) {
        cin >> s;
        buckets[s.length()].push_back(move(s)); 
    }
    
    cout << n << "\n";
    
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
