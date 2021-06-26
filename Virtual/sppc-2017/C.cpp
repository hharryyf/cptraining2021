#include <bits/stdc++.h>
#define MAX_SIZE 32
using namespace std;

vector<pair<int, int>> g[MAX_SIZE];
int visited[MAX_SIZE];
// grid is of size 19 * 31
char s[MAX_SIZE][MAX_SIZE];
int ans[4];
vector<pair<pair<int, int>, pair<int, int>>> candidate;

/*
............>-----<............
.........../.......\...........
........../.........\..........
...>-----<...........>-----<...
../.......\........./.......\..
./.........\......./.........\.
<...........>-----<...........>
.\........./.......\........./.
..\......./.........\......./..
...>-----<...........>-----<...
../.......\........./.......\..
./.........\......./.........\.
<...........>-----<...........>
.\........./.......\........./.
..\......./.........\......./..
...>-----<...........>-----<...
..........\........./..........
...........\......./...........
............>-----<............
*/

void dfs(int v, int mask, int dim) {
    ans[dim] = max(ans[dim], __builtin_popcount(mask));
    for (auto np : g[v]) {
        int nv = np.first;
        int ne = np.second;
        if (!visited[ne]) {
            visited[ne] = 1;
            dfs(nv, mask | (1 << ne), dim);
            visited[ne] = 0;
        }
    }
}

void init() {
    candidate.push_back(make_pair(make_pair(0, 1), make_pair(0, 13)));
    candidate.push_back(make_pair(make_pair(0, 3), make_pair(1, 11)));
    candidate.push_back(make_pair(make_pair(2, 3), make_pair(3, 4)));
    candidate.push_back(make_pair(make_pair(1, 4), make_pair(1, 19)));
    candidate.push_back(make_pair(make_pair(4, 5), make_pair(3, 22)));
    candidate.push_back(make_pair(make_pair(2, 6), make_pair(4, 2)));
    candidate.push_back(make_pair(make_pair(3, 7), make_pair(4, 10)));
    candidate.push_back(make_pair(make_pair(4, 8), make_pair(4, 20)));
    candidate.push_back(make_pair(make_pair(5, 9), make_pair(4, 28)));
    candidate.push_back(make_pair(make_pair(7, 8), make_pair(6, 13)));
    candidate.push_back(make_pair(make_pair(6, 10), make_pair(7, 1)));
    candidate.push_back(make_pair(make_pair(9, 13), make_pair(7, 29)));
    candidate.push_back(make_pair(make_pair(10, 11), make_pair(9, 4)));
    candidate.push_back(make_pair(make_pair(7, 11), make_pair(7, 11)));
    candidate.push_back(make_pair(make_pair(8, 12), make_pair(7, 19)));
    candidate.push_back(make_pair(make_pair(12, 13), make_pair(9, 26)));
    candidate.push_back(make_pair(make_pair(10, 14), make_pair(10, 2)));
    candidate.push_back(make_pair(make_pair(11, 15), make_pair(10, 10)));
    candidate.push_back(make_pair(make_pair(15, 16), make_pair(12, 13)));
    candidate.push_back(make_pair(make_pair(12, 16), make_pair(10, 20)));
    candidate.push_back(make_pair(make_pair(13, 17), make_pair(10, 28)));
    candidate.push_back(make_pair(make_pair(14, 18), make_pair(13, 1)));
    candidate.push_back(make_pair(make_pair(18, 19), make_pair(15, 4)));
    candidate.push_back(make_pair(make_pair(15, 19), make_pair(13, 11)));
    candidate.push_back(make_pair(make_pair(19, 20), make_pair(16, 10)));
    candidate.push_back(make_pair(make_pair(20, 21), make_pair(18, 13)));
    candidate.push_back(make_pair(make_pair(21, 22), make_pair(16, 20)));
    candidate.push_back(make_pair(make_pair(16, 22), make_pair(13, 19)));
    candidate.push_back(make_pair(make_pair(22, 23), make_pair(15, 26)));
    candidate.push_back(make_pair(make_pair(17, 23), make_pair(13, 29)));
}

int main() {
    int i, cnt = 0;
    for (i = 0 ; i < 19; ++i) {
        scanf("%s", s[i]);
    }
    init();
    for (int k = 1; k <= 3; ++k) {
        for (i = 0 ; i < MAX_SIZE; ++i) g[i].clear();
        for (i = 0 ; i < (int) candidate.size(); ++i) {
            if (s[candidate[i].second.first][candidate[i].second.second] == k + '0') {
                g[candidate[i].first.first].emplace_back(candidate[i].first.second, cnt);
                g[candidate[i].first.second].emplace_back(candidate[i].first.first, cnt);
                // cout << "addedge " << candidate[i].first.second << " " << candidate[i].first.first << endl;
                cnt++;
            }
        }        

        for (i = 0 ; i < MAX_SIZE; ++i) {
            memset(visited, 0, sizeof(visited));
            dfs(i, 0, k);
        }
    }
    
    printf("%d %d %d\n", ans[1], ans[2], ans[3]);
    return 0;
}