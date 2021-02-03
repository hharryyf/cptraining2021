#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;

int findL(ll x) {
    int low = 1, high = 100000, ret = 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (1ll * mid * (mid - 1) / 2 <= x) {
            ret = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        vector<int> ret;
        vector<int> ans = vector<int>(1, 1);
        while (N > 0) {
            int step = findL(N);
            ret.push_back(step);
            N -= 1ll * step * (step - 1) / 2;
        }

        ret.push_back(0);
        reverse(ret.begin(), ret.end());
        for (int i = 1; i < (int) ret.size(); ++i) {
            for (int j = 0 ; j < ret[i] - ret[i-1]; ++j) {
                ans.push_back(3);
            }
            ans.push_back(7);
        }

        for (auto v : ans) {
            printf("%d", v);
        }
        printf("\n");
    }
    return 0;
}