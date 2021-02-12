#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
// aim: make b -> subsequence a, by eliminating shortest b[l, r]
char a[MAX_SIZE], b[MAX_SIZE];
int fo[MAX_SIZE], bk[MAX_SIZE];

int main() {
    int i, j, N, M;
    scanf("%s", a + 1);
    scanf("%s", b + 1);
    N = strlen(a + 1), M = strlen(b + 1);
    i = 1, j = 1;
    while (i <= N && j <= M) {
        if (a[i] == b[j]) {
            fo[j] = i;
            ++i, ++j;
        } else {
            ++i;
        }
    }

    if (fo[M]) {
        printf("%s\n", b + 1);
        return 0;
    }

    for (i = 1; i <= M; ++i) {
        if (!fo[i]) {
            fo[i] = MAX_SIZE + 2;
        }
    }

    i = N, j = M;
    bk[M + 1] = MAX_SIZE + 1;
    while (i >= 1 && j >= 1) {
        if (a[i] == b[j]) {
            bk[j] = i;
            --i, --j;
        } else {
            --i;
        }
    }

    int L = 1, R = M;
    for (i = 1; i <= M; ++i) {
        int low = i, high = M, len = MAX_SIZE;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (fo[i-1] < bk[mid + 1]) {
                len = mid - i + 1;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (len < R - L + 1) {
            L = i, R = i + len - 1;
        }
    }

    if (L == 1 && R == M) {
        printf("-\n");
        return 0;
    }

    for (i = 1; i <= M; ++i) {
        if (i < L || i > R) {
            printf("%c", b[i]);
        }
    }
    return 0;
}