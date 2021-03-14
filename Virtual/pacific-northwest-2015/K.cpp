#include <bits/stdc++.h>
#define MAX_SIZE 32
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
int deg[MAX_SIZE * MAX_SIZE], f[MAX_SIZE * MAX_SIZE];
int N;

int idx(int x, int y) {
    return (x - 1) * N + y;
}

void init() {
    int i;
    for (i = 1; i <= N * N; ++i) {
        deg[i] = 0;
        f[i] = i;
    }
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
}

void addedge(int x, int y) {
    deg[x]++, deg[y]++;
    unionset(x, y);
} 

int X, Y;

bool valid(int x, int y) {
    if (x <= 0 || x > N || y <= 0 || y > N) return false;
    if (st[x][y] == 'W' || (st[x][y] == 'B' && (x != X || y != Y))) return false;
    return true;
}

bool check(int x, int y) {
    int i, j;
    bool ok = false;
    init();
    // printf("validate %d %d\n", x, y);
    X = x, Y = y;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (st[i][j] == 'W') {
                ok = false;
                if (valid(i-1, j-1) && valid(i+1, j+1) && ((i+j+2) % 4 == (x+y) % 4)) {
                    ok = true;
                    addedge(idx(i-1, j-1), idx(i+1, j+1));
                }

                if (valid(i-1, j+1) && valid(i+1, j-1) && ((i+j) % 4 == (x+y) % 4)) {
                    ok = true;
                    addedge(idx(i-1, j+1), idx(i+1, j-1));
                }
                if (!ok) {
                    //printf("%d %d\n", i, j);
                    return false;
                }
            }
        }
    }

    set<int> st;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (deg[idx(i, j)] != 0 && find(idx(i, j)) != find(idx(x, y))) {
                return false;
            }

            if (deg[idx(i, j)] % 2 == 1) {
                st.insert(idx(i, j));
            }
        }
    }
    //printf("%d %d\n", x, y);
    if ((int) st.size() > 2) return false;
    if (!st.empty() && st.find(idx(x, y)) == st.end()) return false;
    return true;
}

int main() {
    int i, j;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s", st[i] + 1);
    }

    vector<pair<int, char>> ans;
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (st[i][j] == 'B') {
                if (check(i, j)) {
                    ans.emplace_back('a' + j - 1, N - i + 1);
                }
            }
        }
    }

    if (ans.empty()) {
        printf("None\n");
    } else if ((int) ans.size() == 1) {
        printf("%c%d\n", ans[0].first, ans[0].second);
    } else {
        printf("Multiple\n");
    }
    return 0;
}