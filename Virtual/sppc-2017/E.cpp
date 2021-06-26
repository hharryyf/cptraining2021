#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 101
int a[MAX_SIZE][MAX_SIZE];

void check(int N) {
    int i, j;
    if (N == 1 && a[1][1] == 1) {
        printf("wrong answer\n");
    } 
    if (N == 1) return;
    for (i = 1; i <= N; ++i) {
        int cnt = 0;
        for (j = 1; j <= N; ++j) {
            if (i == j && a[i][j] == 1) {
                printf("wrong answer for N=%d\n", N);
                exit(1);
            }
            if (i == j) continue;
            if (a[i][j] == a[j][i]) {
                printf("wrong answer for N=%d\n", N);
                exit(1);
            }
            cnt += a[i][j];
        }

        if (cnt != N/ 2) {
            printf("wrong answer for N=%d\n", N);
            exit(1);
        }
    }
}

void solve(int N) {
    assert(N % 2 == 1);
    int i, j;
    for (i = 1; i <= 99; ++i) {
        for (j = 1; j <= 99; ++j) {
            a[i][j] = 0;
        }
    }

    for (i = 1; i <= N; ++i) {
        int sm = 0;
        for (j = 1; j <= N; ++j) {
            if (i == j) continue;
            if (i > j) {
                sm += a[i][j];
            } else {
                if (sm < N / 2) {
                    a[i][j] = 1;
                    sm++;
                    a[j][i] = 0;
                } else {
                    a[i][j] = 0;
                    a[j][i] = 1;
                }
            }
        }
    }
}

void test() {
    int i;
    for (i = 1; i <= 99; i += 2) {
        solve(i);
        check(i);
    }
}

int main() {
    test();
    int N;
    scanf("%d", &N);
    solve(N);
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (a[i][j]) {
                printf("%d %d\n", i, j);
            }
        }
    }
    return 0;
}