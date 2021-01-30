#include <bits/stdc++.h>
#define MAX_SIZE 1000011
typedef long long ll;
using namespace std;

int R[MAX_SIZE], C[MAX_SIZE];
char s[4];
ll rsum, csum, rcnt, ccnt;
int N;

int main() {
    int Q;
    freopen("adjustment.in", "r", stdin);
    freopen("adjustment.out", "w", stdout);
    scanf("%d%d", &N, &Q);
    rcnt = ccnt = N;
    rsum = csum = 1ll * N * (N + 1) / 2;
    while (Q-- > 0) {
        int id;
        scanf("%s%d", s, &id);
        if (s[0] == 'R') {
            if (R[id]) {
                printf("0\n");
            } else {
                printf("%I64d\n", csum + ccnt * id);
                rcnt--;
                rsum -= id;
            }
            R[id] = 1;
        } else {
            if (C[id]) {
                printf("0\n");
            } else {
                printf("%I64d\n", rsum + rcnt * id);
                ccnt--;
                csum -= id;
            }
            C[id] = 1;
        }
    }
    return 0;
}