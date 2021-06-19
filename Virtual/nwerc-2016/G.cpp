#include <bits/stdc++.h>
typedef long long ll;
#define MAX_SIZE 100111
using namespace std;

const int inf = 1e8;
int candy[MAX_SIZE];
vector<int> family[MAX_SIZE];
multiset<int> selected[MAX_SIZE];
multiset<pair<int, int>> candidate[MAX_SIZE];
int timestamp[MAX_SIZE << 2];
pair<int, int> mp[MAX_SIZE << 2];
char ss[24];
unordered_map<string, int> level;
unordered_map<string, int> group;
int F, N;

int undo(int gid) {
    if (candidate[gid].empty() || selected[gid].empty() || *selected[gid].rbegin() <= candidate[gid].begin()->first) return 0;
    auto p = *selected[gid].rbegin();
    selected[gid].erase(selected[gid].find(p));
    candy[gid] += p;
    candidate[gid].insert(make_pair(p, inf));
    return 1;
}

ll envolve(int gid) {
    ll delta = 0;
    while (!candidate[gid].empty()) {
        if (candy[gid] < candidate[gid].begin()->first) {
            if (!undo(gid)) break;
            delta--;
        }

        if (candidate[gid].empty()) break;
        auto p = *candidate[gid].begin();
        candidate[gid].erase(candidate[gid].find(p));
        selected[gid].insert(p.first);
        candy[gid] -= p.first;
        if (p.second + 1 < (int) family[gid].size()) {
            candidate[gid].insert(make_pair(family[gid][p.second + 1], p.second + 1));
        }
        delta++;
    }
    return delta;
}

int main() {
    int i, n, j;
    scanf("%d", &F);
    for (i = 1; i <= F; ++i) {
        scanf("%d", &n);
        for (j = 0 ; j < n - 1; ++j) {
            int v;
            scanf("%s%d", ss, &v);
            group[ss] = i;
            family[i].push_back(v);
            level[ss] = j;
        }
        candy[i] = -1;
        scanf("%s", ss);
        group[ss] = i;
        level[ss] = n - 1;
    }

    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d%s", &timestamp[i], ss);
        mp[i].first = group[ss];
        mp[i].second = level[ss];
    }

    ll ans = 0, curr = 0;
    for (i = 1, j = 1; i <= N; ++i) {
        candy[mp[i].first] += 4;
        if (mp[i].second < (int) family[mp[i].first].size()) {
            candidate[mp[i].first].insert(make_pair(family[mp[i].first][mp[i].second], mp[i].second));
        }
        curr += envolve(mp[i].first);
        while (j < i && timestamp[i] - timestamp[j] >= 1800) ++j;
        ans = max(ans, curr * 1000 + (N + i - j + 1) * 100);
    }

    printf("%lld\n", ans);
    return 0;
}