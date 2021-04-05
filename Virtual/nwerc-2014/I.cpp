#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define MAX_SIZE 15
typedef long long ll;
using namespace std;

ll L, a[MAX_SIZE][MAX_SIZE];
vector<int> inner[5011];
int N, tol = 0, visited[MAX_SIZE];
unordered_set<ll> mp[MAX_SIZE][MAX_SIZE];
void dfs(int low, int step) {
    int i;
    if (step == 0) {
        for (i = 1; i <= N; ++i) {
            if (visited[i]) inner[tol].push_back(i);
        }

        tol++;
        return;
    }

    for (i = low; i <= N; ++i) {
        visited[i] = 1;
        dfs(i + 1, step - 1);
        visited[i] = 0;
    }
}   

int main() {
    int i, j, k, l;
    scanf("%d%I64d", &N, &L);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            scanf("%I64d", &a[i][j]);
        }
    }

    dfs(1, (N + 1) / 2);
    //printf("tol= %d\n", tol);
    for (i = 0 ; i < tol; ++i) {
        for (k = 1 ; k <= N; ++k) {
            for (j = 1; j <= N; ++j) {
                mp[k][j].clear();
            }
        }

        memset(visited, 0, sizeof(visited));
        for (auto v : inner[i]) {
            visited[v] = 1;
        }

        bool flag = true;
        //int cc = 0;
        while (flag) {
            ll sm = 0;
            if (inner[i].front() > inner[i].back() || inner[i].front() != 1) {
                flag = next_permutation(inner[i].begin(), inner[i].end());
                continue;
            }

            for (j = 0 ; j < (int) inner[i].size() - 1; ++j) {
                sm += a[inner[i][j + 1]][inner[i][j]];
            } 

            if (sm <= L) mp[inner[i].front()][inner[i].back()].insert(sm);
            //cc++;
            flag = next_permutation(inner[i].begin(), inner[i].end());
        }
        //printf("%d\n", cc);
        vector<int> disc;
        
        for (j = 1; j <= N; ++j) {
            if (!visited[j]) {
                disc.push_back(j);
            }
        }

        flag = true;
        while (flag) {
            if (disc.front() > disc.back()) {
                flag = next_permutation(disc.begin(), disc.end());
                continue;
            }
            ll sm = 0;
            for (j = 0 ; j < (int) disc.size() - 1; ++j) {
                sm += a[disc[j]][disc[j + 1]];
            }

            if (sm <= L) {
                int x = disc.front(), y = disc.back();
                for (int kk = 0; kk < (int) inner[i].size(); ++kk) {
                    for (int ll = kk; ll < (int) inner[i].size(); ++ll) {
                        k = inner[i][kk], l = inner[i][ll];
                        if (mp[k][l].find(L - sm - a[k][x] - a[l][y]) != mp[k][l].end()) {
                            printf("possible\n");
                            return 0;
                        }

                        if (mp[k][l].find(L - sm - a[k][y] - a[l][x]) != mp[k][l].end()) {
                            printf("possible\n");
                            return 0;
                        }
                    }
                }
            }

            flag = next_permutation(disc.begin(), disc.end());
        }
    }

    printf("impossible\n");
    return 0;
}