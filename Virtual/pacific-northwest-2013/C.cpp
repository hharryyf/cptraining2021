#include <bits/stdc++.h>
#define MAX_SIZE 9
using namespace std;
unordered_map<string, double> dp;
unordered_map<string, double> dp2;
int a[MAX_SIZE], tmp[MAX_SIZE];

double dfs(string &curr) {
    int i, j, sz = curr.size();
    double ret = 0.0;
    int cnt = 0;
    bool valid = true;
    for (i = 0 ; i < sz - 1; ++i) {
        if (curr[i] > curr[i+1]) {
            valid = false;
            break;
        }
    }
    if (valid) return 0.0;
    if (dp.find(curr) != dp.end()) return dp[curr];
    for (i = 0 ; i < sz; ++i) {
        for (j = i + 1; j < sz; ++j) {
            if (curr[i] > curr[j]) {
                cnt += 2;
                swap(curr[i], curr[j]);
                ret = ret + 2.0 * (dfs(curr) + 1.0)  / (1.0 * sz * sz);
                swap(curr[i], curr[j]);
            }
        }
    }

    return dp[curr] = (ret + 1 - 1.0 * cnt / (sz * sz)) / cnt * (sz * sz);
}

double dfs2(string &curr) {
    int i, sz = curr.size();
    double ret = 0.0;
    int cnt = 0;
    bool valid = true;
    for (i = 0 ; i < sz - 1; ++i) {
        if (curr[i] > curr[i+1]) {
            valid = false;
            break;
        }
    }
    if (valid) return 0.0;
    if (dp2.find(curr) != dp2.end()) return dp2[curr];
    for (i = 0 ; i < sz - 1; ++i) {
        if (curr[i] > curr[i+1]) {
            cnt += 1;
            swap(curr[i], curr[i+1]);
            ret = ret + (dfs2(curr) + 1.0)  / (1.0 * (sz - 1));
            swap(curr[i], curr[i+1]);
        }
    }

    return dp2[curr] = (ret + 1 - 1.0 * cnt / (sz - 1)) / cnt * (sz - 1);
}

int main() {
    int T, N, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 0 ; i < N; ++i) {
            scanf("%d", &a[i]);
            tmp[i] = a[i];
        }
        sort(tmp, tmp + N);
        vector<int> disc;
        for (i = 0 ; i < N; ++i) {
            if (i == 0 || tmp[i] != tmp[i-1]) disc.push_back(tmp[i]);
        }

        string res;
        for (i = 0 ; i < N; ++i) {
            int idx = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin();
            res += (idx + '0');
        }

        printf("Monty %.6lf Carlos %.6lf\n", dfs(res), dfs2(res));
    }
    return 0;
}