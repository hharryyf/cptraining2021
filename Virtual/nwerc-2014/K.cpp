#include <bits/stdc++.h>
#define MAX_SIZE 2011
using namespace std;
typedef long long ll;
int N, S, T;
int k[MAX_SIZE];
set<int> interesting;
multiset<int> slot;
map<int, ll> ans;

ll solve(int start) {
    int i;
    ll ret = 0;
    slot.clear();
    for (i = 0 ; i < N; ++i) {
        slot.insert(k[i]);
    }

    while (!slot.empty()) {
        int nxt = 0;
        if (start > *slot.rbegin()) {
            nxt = *slot.begin();
        } else {
            nxt = *slot.lower_bound(start);
        }

        slot.erase(slot.find(nxt));
        ret = ret + (nxt + S - start) % S;
        ret = ret + T;
        start = (nxt + T % S) % S;
    }

    return ret;
}

int main() {
    int i;
    scanf("%d%d%d", &N, &S, &T);
    for (i = 0; i < N; ++i) {
        scanf("%d", &k[i]);
        interesting.insert(k[i]);
    }

    for (auto v : interesting) {
        ans[v] = solve(v);
    }

    ll minn = 7e18, maxx, tol = 0;
    for (auto iter : ans) {
        minn = min(minn, iter.second);
    }

    if (S == 1) {
        cout << minn << endl;
        cout << minn << endl;
        cout << minn << "/1" << endl;
        return 0;
    }
    
    vector<pair<int, ll>> pos;
    maxx = minn;
    for (auto iter : ans) {
        pos.emplace_back(iter.first, iter.second);
        maxx = max(maxx, iter.second);
        tol = tol + iter.second;
    }
    int sz = pos.size();
    for (i = 0 ; i < sz; ++i) {
        if ((pos[i].first + 1) % S != pos[(i + 1) % sz].first) {
            int gap = (pos[(i + 1) % sz].first - pos[i].first - 1 + S) % S;
            maxx = max(maxx, pos[(i + 1) % sz].second + gap);
            tol += 1ll * (gap) * (gap + 1) / 2 + 1ll * gap * pos[(i + 1) % sz].second;
        }
    }

    ll g = __gcd(tol, 1ll * S);
    tol = tol / g;
    S = S / g;
    cout << minn << endl;
    cout << maxx << endl;
    cout << tol << "/" << S << endl;
    return 0;
}