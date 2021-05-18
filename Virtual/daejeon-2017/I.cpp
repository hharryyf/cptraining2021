#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

int p[MAX_SIZE], st[MAX_SIZE];

int main() {
    int N, i, j = 0;
    scanf("%d", &N);
    for (i = N ; i >= 1; --i) {
        scanf("%d", &st[i]);
    }
    st[N + 1] = -1;
    for (i = 2; i <= N; ++i) {
        while (j > 0 && st[i] != st[j+1]) j = p[j];
        if (st[i] == st[j+1]) ++j;
        p[i] = j;
    }

    int ans = 3 * N;
    int k = -1, pp = -1;
    for (i = 1; i <= N; ++i) {
        if (ans > N - p[i]) {
            ans = N - p[i];
            k = N - i;
            pp = i - p[i]; 
        }
    }

    printf("%d %d\n", k, pp);
    return 0;
}