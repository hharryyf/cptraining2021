#include <bits/stdc++.h>
#define MAX_SIZE 1000111
using namespace std;

char shift[MAX_SIZE], text[MAX_SIZE];

int main() {
    while (scanf("%s", shift) != EOF) {
        if (shift[0] == '0') break;
        scanf("%s", text);
        int i, N = strlen(shift), M = strlen(text);
        for (i = N; i < M; ++i) {
            shift[i] = shift[i % N];
        }

        for (i = 0; i < M; ++i) {
            int id = (shift[i] - 'A' + 1) % 26;
            int ord = (text[i] - 'A' + id) % 26;
            text[i] = 'A' + ord;
        }
        printf("%s\n", text);
    }
    return 0;
}