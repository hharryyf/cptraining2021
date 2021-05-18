#include <bits/stdc++.h>

using namespace std;

int L, R, U, D, cx, cy;
void walk(char &dir, int change) {
    if (dir == 'R') {
        printf("%d ", R + 1 - cx);
        cx = R + 1, R++;
        if (change == 1) {
            dir = 'D';
        } else {
            dir = 'U';
        }
    } else if (dir == 'L') {
        L--;
        printf("%d ", cx - L);
        cx = L;
        if (change == 1) {
            dir = 'U';
        } else {
            dir = 'D';
        }
    } else if (dir == 'U') {
        U++;
        printf("%d ", U - cy);
        cy = U;
        if (change == 1) {
            dir = 'R';
        } else {
            dir = 'L';
        }
    } else {
        D--;
        printf("%d ", cy - D);
        cy = D;
        if (change == 1) {
            dir = 'L';
        } else {
            dir = 'R';
        }
    }
}

int main() {
    int N, x, y;
    char dir = 'R';
    scanf("%d", &N);
    while (N-- > 0) {
        scanf("%d%d", &x, &y);
        walk(dir, y);
    }
    return 0;
}