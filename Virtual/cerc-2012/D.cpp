#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int pre[MAX_SIZE], nxt[MAX_SIZE], L[MAX_SIZE], R[MAX_SIZE];
int a[MAX_SIZE], tmp[MAX_SIZE];
vector<int> disc;
int N;

inline bool divc(int l, int r) {
    if (l >= r) return 1;
    // printf("solve %d %d\n", l, r);
    int x = l, y = r;
    while (x <= y) {
        if (pre[x] < l && nxt[x] > r) {
            return divc(l, x - 1) && divc(x + 1, r);
        }

        if (pre[y] < l && nxt[y] > r) {
            return divc(l, y - 1) && divc(y + 1, r);
        }

        x++, y--;
    }

    return 0;
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            tmp[i] = a[i];
        }

        sort(tmp + 1, tmp + 1 + N);
        disc.clear();
        for (i = 1; i <= N; ++i) {
            if (i == 1 || tmp[i] != tmp[i-1]) {
                disc.push_back(tmp[i]);
            }
        }

        for (i = 1; i <= N; ++i) {
            a[i] = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin() + 1;
        }

        for (i = 1; i <= N; ++i) {
            L[a[i]] = 0, R[a[i]] = N + 1;
        }

        for (i = 1; i <= N; ++i) {
            pre[i] = L[a[i]];
            L[a[i]] = i;
        }

        for (i = N; i >= 1; --i) {
            nxt[i] = R[a[i]];
            R[a[i]] = i;
        }

        printf("%s\n", divc(1, N) ? "non-boring" : "boring");
    }
    return 0;
}