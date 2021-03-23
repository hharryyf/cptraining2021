#include <bits/stdc++.h>

using namespace std;

int a[6], b[6];

int main() {
    int i, j, cnt = 0;
    for (i = 0 ; i < 6; ++i) scanf("%d", &a[i]);
    for (i = 0 ; i < 6; ++i) scanf("%d", &b[i]);
    for (i = 0 ; i < 6; ++i) {
        for (j = 0 ; j < 6; ++j) {
            if (a[i] > b[j]) {
                cnt++;
            }
        }
    }

    printf("%d/%d\n", cnt/__gcd(cnt, 36), 36/__gcd(cnt, 36));
    return 0;
}