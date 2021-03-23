#include <bits/stdc++.h>

using namespace std;

int a[1000011], b[1000011];

int main() {
    int i, N, sm;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) scanf("%d", &a[i]);
    for (i = 0 ; i < N; ++i) {
        if (a[i] > 2) {
            printf("NO\n");
            return 0;
        }
        sm = sm + a[i];
        sm %= 2;
    }

    if (sm > 0) {
        printf("NO\n");
        return 0;
    }
    

    for (i = 0 ; i < N - 1; ++i) {
        if (abs(b[i] - 1) == a[i]) {
            b[i+1] += 1;
        } else if (abs(b[i]) == a[i]) {
            b[i+1] = 0;
        } else if (abs(b[i] + 1) == a[i]) {
            b[i+1] -= 1;
        } else {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    return 0;
}