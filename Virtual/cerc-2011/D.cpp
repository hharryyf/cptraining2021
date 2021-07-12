#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

char g[MAX_SIZE][MAX_SIZE];
char t[MAX_SIZE][MAX_SIZE];
int main() {
    int N, i, j;
    while (scanf("%d", &N) != EOF) {
        if (N == 0) break;
        for (i = 0 ; i < N; ++i) scanf("%s", g[i]);
        for (i = 0 ; i < N; ++i) scanf("%s", t[i]);
        vector<char> ret;
        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                if (g[i][j] == 'O') {
                    ret.push_back(t[i][j]);
                }
            }
        }

        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                int c = i, r = N - j - 1;
                if (g[r][c] == 'O') {
                    ret.push_back(t[i][j]);
                }
            }
        }

        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                int c = N - j - 1, r = N - i - 1;
                if (g[r][c] == 'O') {
                    ret.push_back(t[i][j]);
                }
            }
        }

        
        for (i = 0 ; i < N; ++i) {
            for (j = 0 ; j < N; ++j) {
                int c = N - i - 1, r = j;
                if (g[r][c] == 'O') {
                    ret.push_back(t[i][j]);
                }
            }
        }
        for (auto v : ret) {
            printf("%c", v);
        }
        printf("\n");
    }
    return 0;
}