#include <bits/stdc++.h>

using namespace std;

int calc(int x, int y) {
    for (int i = 1; i <= 10; ++i) {
        if (x * x + y * y <= 400 * i * i) return 11 - i; 
    }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, score = 0;
        scanf("%d", &N);
        while (N-- > 0) {
            int x, y;
            scanf("%d%d", &x, &y);
            score += calc(x, y);
        }
        printf("%d\n", score);        
    }
    return 0;
}