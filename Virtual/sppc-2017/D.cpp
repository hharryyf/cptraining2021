#include <bits/stdc++.h>
#define MAX_SIZE 100111
using namespace std;
typedef long long ll;
char s[MAX_SIZE];
int p[4];
ll K;
int len, N;

void print(int id) {
    for (int i = id * len; i < len + id * len; ++i) {
        printf("%c", s[i]);
    }
}

int main() {
    int i;
    scanf("%d%lld", &N, &K);
    scanf("%s", s);
    if (K % 3 == 0) {
        p[1] = 1, p[2] = 2, p[3] = 3;
    } else if (K % 3 == 1) {
        p[1] = 3, p[2] = 1, p[3] = 2;
    } else {
        p[1] = 2, p[2] = 3, p[3] = 1;
    }

    len = N / 4;
    for (i = 0; i < 4; ++i) {
        print(p[i]);
    }
    printf("\n");
    return 0;
}