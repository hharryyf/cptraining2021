#include <bits/stdc++.h>

using namespace std;

struct state {
    double p[5];
};

int a[5];
unordered_map<int, state> mp;
int N, K;

int encode(vector<int> &vc) {
    int ret = 0;
    for (auto v : vc) {
        ret = ret * 52 + v;
    }
    return ret;
}

state solve(vector<int> &vc) {
    int i, j, sm = 0, mx = 0;
    int cmp = encode(vc);
    for (i = 0 ; i < N; ++i) {
        sm += vc[i];
        mx = max(vc[i], mx);
    }

    state ret;
    for (i = 0 ; i < N; ++i) {
        ret.p[i] = 0;
    }

    if (sm == K) {
        int cnt = 0;
        for (i = 0 ; i < N; ++i) {
            if (vc[i] == mx) cnt++;
        }   

        for (i = 0 ; i < N; ++i) {
            ret.p[i] = 1.0 * (vc[i] == mx) / cnt;
        } 
        return ret;
    }

    if (mp.find(cmp) != mp.end()) return mp[cmp];

    for (i = 0 ; i < N; ++i) {
        vc[i] += 1;
        auto nxt = solve(vc);
        vc[i] -= 1;
        for (j = 0 ; j < N; ++j) {
            ret.p[j] += nxt.p[j] * vc[i] / sm;
        }
    }

    return mp[cmp] = ret;
}

int main() {
    while (scanf("%d%d", &N, &K) != EOF) {
        int i;
        mp.clear();
        for (i = 0 ; i < N; ++i) {
            scanf("%d", &a[i]);
        }

        vector<int> vc(N);
        for (i = 0 ; i < N; ++i) {
            vc[i] = a[i];
        }
        state ans = solve(vc);
        for (i = 0 ; i < N; ++i) {
            printf("pub %d: %.2lf %%\n", i + 1, ans.p[i] * 100);
        }
    }    
    return 0;
}