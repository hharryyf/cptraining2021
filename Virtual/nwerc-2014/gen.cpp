#include <bits/stdc++.h>

using namespace std;

int main() {
    printf("14 10\n");
    for (int i = 0 ; i < 14; ++i) {
        for (int j = 0 ; j < 14; ++j) {
            if (i == j) {
                printf("0 ");
            } else {
                printf("%d ", i + j);
            }
        }
        printf("\n");
    }
    return 0;
}