#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<ll> ret;

void gen(int pos, int cnt, ll curr) {
    if (pos < 0) {
        ret.push_back(curr);
        return;
    }

    if (cnt == 0) {
        gen(pos - 1, cnt, curr * 10);
    } else {
        for (int i = 0 ; i <= 9; ++i) {
            gen(pos - 1, cnt - (i != 0), curr * 10 + i);
        }
    }
}

int main() {
    ret.push_back(1e18);
    gen(17, 3, 0);
    sort(ret.begin(), ret.end());
    auto it = unique (ret.begin(), ret.end());
    ret.resize(distance(ret.begin(),it));
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        ll L, R;
        scanf("%I64d%I64d", &L, &R);
        int idx1 = upper_bound(ret.begin(), ret.end(), R) - ret.begin() - 1;
        int idx2 = lower_bound(ret.begin(), ret.end(), L) - ret.begin() - 1;
        printf("%d\n", idx1 - idx2);
    }
    return 0;
}