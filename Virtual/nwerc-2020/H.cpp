#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int b[MAX_SIZE];
list<int> a;

int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 0 ; i < n; ++i) scanf("%d", &b[i]);
    sort(b, b + n);
    for (i = 0 ; i < n; ++i) {
        a.push_back(b[i]);
    }
    int t = 0;
    for (i = n - 1; i >= 0; --i) {
        if (t % 2 == 0) {
            b[i] = a.back();
            a.pop_back();
        } else {
            b[i] = a.front();
            a.pop_front();
        }
        t++;
    }

    for (i = 0 ; i <= n - 1; ++i) {
        printf("%d ", b[i]);
    }
    return 0;
}