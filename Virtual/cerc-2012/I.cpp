#include <bits/stdc++.h>
#define MAX_SIZE 111
typedef long long ll;
using namespace std;

struct line {
    ll A, B, C;
};

line li[MAX_SIZE];
bitset<100> pt[50011];
int N, M;

const bool cmp(bitset<100> &a, bitset<100> &b) {
    int i;
    for (i = 0 ; i < 100; ++i) {
        if (a[i] < b[i]) return 1;
        if (a[i] > b[i]) return 0;
    }
    return 0;
}

int main() {
    int T, i, j;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d", &N, &M);
        for (i = 0 ; i < N; ++i) {
            scanf("%lld%lld%lld", &li[i].A, &li[i].B, &li[i].C);
        }

        for (i = 0 ; i < M; ++i) {
            for (j = 0 ; j < 100; ++j) {
                pt[i].reset(j);
            }
        }

        int area = 1;
        for (i = 0 ; i < N; ++i) {
            area++;
            for (j = 0 ; j < i; ++j) {
                if (li[i].A * li[j].B != li[i].B * li[j].A) {
                    area++;
                }
            }
        }

        int cnt = 1;
        for (i = 0 ; i < M; ++i) {
            ll x, y;
            scanf("%lld%lld", &x, &y);
            for (j = 0 ; j < N; ++j) {
                if (li[j].A * x + li[j].B * y + li[j].C > 0) {
                    pt[i].set(j);
                }
            }
        }

        sort(pt, pt + M, cmp);
        for (i = 0; i < M - 1; ++i) {
            if (pt[i] != pt[i+1]) {
                cnt++;
            }
        }
        
        // printf("%d %d\n", cnt, area);

        if (cnt == area) {
            printf("PROTECTED\n");
        } else {
            printf("VULNERABLE\n");
        }
    }
    return 0;
}