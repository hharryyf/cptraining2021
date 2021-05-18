#include <bits/stdc++.h>

using namespace std;

int visited[4][4];
int pw[16], a, b;
unordered_set<int> ret;
int calc(int x, int y) {
    return visited[x][y] * pw[x * 4 + y];
}

int judge() {
    if (visited[0][0] == 2 && visited[0][1] == 2 && visited[0][2] == 2) return 2;
    if (visited[0][3] == 2 && visited[0][1] == 2 && visited[0][2] == 2) return 2;
    if (visited[1][0] == 2 && visited[1][1] == 2 && visited[1][2] == 2) return 2;
    if (visited[1][3] == 2 && visited[1][1] == 2 && visited[1][2] == 2) return 2;
    if (visited[3][0] == 2 && visited[3][1] == 2 && visited[3][2] == 2) return 2;
    if (visited[3][3] == 2 && visited[3][1] == 2 && visited[3][2] == 2) return 2;
    if (visited[2][0] == 2 && visited[2][1] == 2 && visited[2][2] == 2) return 2;
    if (visited[2][3] == 2 && visited[2][1] == 2 && visited[2][2] == 2) return 2;
    if (visited[0][0] == 2 && visited[1][0] == 2 && visited[2][0] == 2) return 2;
    if (visited[3][0] == 2 && visited[1][0] == 2 && visited[2][0] == 2) return 2;
    if (visited[0][1] == 2 && visited[1][1] == 2 && visited[2][1] == 2) return 2;
    if (visited[3][1] == 2 && visited[1][1] == 2 && visited[2][1] == 2) return 2;
    if (visited[0][3] == 2 && visited[1][3] == 2 && visited[2][3] == 2) return 2;
    if (visited[3][3] == 2 && visited[1][3] == 2 && visited[2][3] == 2) return 2;
    if (visited[0][2] == 2 && visited[1][2] == 2 && visited[2][2] == 2) return 2;
    if (visited[3][2] == 2 && visited[1][2] == 2 && visited[2][2] == 2) return 2;
    
    if (visited[0][0] == 1 && visited[0][1] == 1 && visited[0][2] == 1) return 1;
    if (visited[0][3] == 1 && visited[0][1] == 1 && visited[0][2] == 1) return 1;
    if (visited[1][0] == 1 && visited[1][1] == 1 && visited[1][2] == 1) return 1;
    if (visited[1][3] == 1 && visited[1][1] == 1 && visited[1][2] == 1) return 1;
    if (visited[3][0] == 1 && visited[3][1] == 1 && visited[3][2] == 1) return 1;
    if (visited[3][3] == 1 && visited[3][1] == 1 && visited[3][2] == 1) return 1;
    if (visited[2][0] == 1 && visited[2][1] == 1 && visited[2][2] == 1) return 1;
    if (visited[2][3] == 1 && visited[2][1] == 1 && visited[2][2] == 1) return 1;
    if (visited[0][0] == 1 && visited[1][0] == 1 && visited[2][0] == 1) return 1;
    if (visited[3][0] == 1 && visited[1][0] == 1 && visited[2][0] == 1) return 1;
    if (visited[0][1] == 1 && visited[1][1] == 1 && visited[2][1] == 1) return 1;
    if (visited[3][1] == 1 && visited[1][1] == 1 && visited[2][1] == 1) return 1;
    if (visited[0][3] == 1 && visited[1][3] == 1 && visited[2][3] == 1) return 1;
    if (visited[3][3] == 1 && visited[1][3] == 1 && visited[2][3] == 1) return 1;
    if (visited[0][2] == 1 && visited[1][2] == 1 && visited[2][2] == 1) return 1;
    if (visited[3][2] == 1 && visited[1][2] == 1 && visited[2][2] == 1) return 1;

    if (visited[0][0] == 2 && visited[1][1] == 2 && visited[2][2] == 2) return 2;
    if (visited[3][3] == 2 && visited[1][1] == 2 && visited[2][2] == 2) return 2;
    if (visited[0][1] == 2 && visited[1][2] == 2 && visited[2][3] == 2) return 2;
    if (visited[3][0] == 2 && visited[2][1] == 2 && visited[1][2] == 2) return 2;
    if (visited[2][1] == 2 && visited[1][2] == 2 && visited[0][3] == 2) return 2;
    if (visited[2][0] == 2 && visited[1][1] == 2 && visited[0][2] == 2) return 2;
    if (visited[3][1] == 2 && visited[2][2] == 2 && visited[1][3] == 2) return 2;
    if (visited[1][0] == 2 && visited[2][1] == 2 && visited[3][2] == 2) return 2;

    if (visited[1][0] == 1 && visited[2][1] == 1 && visited[3][2] == 1) return 1;
    if (visited[3][1] == 1 && visited[2][2] == 1 && visited[1][3] == 1) return 1;
    if (visited[0][0] == 1 && visited[1][1] == 1 && visited[2][2] == 1) return 1;
    if (visited[3][3] == 1 && visited[1][1] == 1 && visited[2][2] == 1) return 1;
    if (visited[0][1] == 1 && visited[1][2] == 1 && visited[2][3] == 1) return 1;
    if (visited[3][0] == 1 && visited[2][1] == 1 && visited[1][2] == 1) return 1;
    if (visited[2][1] == 1 && visited[1][2] == 1 && visited[0][3] == 1) return 1;
    if (visited[2][0] == 1 && visited[1][1] == 1 && visited[0][2] == 1) return 1;
    return 0;
}

void dfs(int px, int py, int step, int state) {
    if (step >= 17) return;
    int val = judge(), mv = 2 - ((step & 1) ^ 1), i, j;
    if (visited[a][b] == 1) return;
    if (visited[a][b] == 2 && (px != a || py != b)) return;
    if (val == 1) return;
    if (val == 2) {
        if (px == a && py == b) ret.insert(state);
        return;
    }

    for (j = 0; j < 4; ++j) {
        for (i = 0 ; i < 4; ++i) {
            if (visited[i][j] == 0) {
                visited[i][j] = mv;
                dfs(i, j, step + 1, state + calc(i, j));
                visited[i][j] = 0;
                break;
            }
        }
    }
}

int main() {
    int i, x;
    scanf("%d%d%d", &x, &a, &b);
    x--, a--, b--;
    pw[0] = 1;
    for (i = 1; i < 16; ++i) pw[i] = pw[i-1] * 3;
    visited[0][x] = 1;
    dfs(0, x, 1, calc(0, x));
    printf("%d\n", (int) ret.size());
    return 0;
}