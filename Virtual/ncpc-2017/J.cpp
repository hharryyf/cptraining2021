#include <bits/stdc++.h>

using namespace std;

int main() {
    int L, R;
    scanf("%d%d", &L, &R);
    if (L == 0 && R == 0) {
        printf("Not a moose\n");
        return 0;
    }

    if (L == R) {
        printf("Even ");
    } else {
        printf("Odd ");
    }
    printf("%d\n", max(L, R) * 2);
    return 0;
}