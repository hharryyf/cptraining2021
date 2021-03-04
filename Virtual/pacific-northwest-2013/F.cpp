#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

vector<int> g[MAX_SIZE];
int sm[MAX_SIZE];

void init() {
    for (int i = 1; i < MAX_SIZE; ++i) {
        for (int j = i; j < MAX_SIZE; j += i) {
            g[j].push_back(i);
            sm[j] += i;
        }
    }
}

int main() {
    int v, i;
    init();
    while (scanf("%d", &v) != EOF) {
        if (v == -1) break;
        if (sm[v] == 2 * v) {
            g[v].pop_back();
            printf("%d = %d", v, g[v][0]);
            for (i = 1; i < (int) g[v].size(); ++i) {
                printf(" + %d", g[v][i]);
            }
            printf("\n");
        } else {
            printf("%d is NOT perfect.\n", v);
        }
    }
    return 0;
}