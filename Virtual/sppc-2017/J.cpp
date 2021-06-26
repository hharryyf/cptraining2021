#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;
typedef long long ll;
multiset<int> st;
int w[MAX_SIZE << 2];
int C, R;

int main() {
    int i;
    ll ans = 0;
    scanf("%d%d", &C, &R);
    for (i = 1; i <= R * 3; ++i) {
        scanf("%d", &w[i]);
    }

    int cnt = C - 1;
    for (i = 1; i <= R * 3; ++i) {
        if (w[i] <= C) {
            st.insert(w[i]);
        } 
    }

    // 2 * C - 2 data used for tree edges
    // R * 2 - (2 * C - 2) used for other edges, these must be the top edges from the remaining
    // R used for weights
    for (i = C; i >= 1; --i) {
        st.erase(st.find(i));
    }

    for (i = 1; i <= C - 2; ++i) {
        st.erase(st.find(*st.rbegin()));
    }
    
    for (i = 1; i <= R * 2 - (2 * C - 2); ++i) {
        if (!st.empty()) {
            st.erase(st.find(*st.rbegin()));
        }
    }

    for (i = 1; i <= R * 3; ++i) {
        if (w[i] > C) st.insert(w[i]);
    }

    for (auto v : st) {
        if (cnt <= 0) break;
        ans += v;
        cnt--;
    }
    printf("%lld\n", ans);
    return 0;
}