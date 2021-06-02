#include <bits/stdc++.h>

using namespace std;

map<string, int> mp;
vector<int> g[511];
int dp[511][2011];
int N;

void init() {
    memset(dp, 0, sizeof(dp));
    for (int i = 0 ; i < 511; ++i) g[i].clear();
    mp.clear();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        scanf("%d", &N);
        getchar();
        
    }
    return 0;
}