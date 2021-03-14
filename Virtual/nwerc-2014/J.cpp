#include <bits/stdc++.h>

using namespace std;

map<string, int> mp1, mp2;
char st[17];
int N;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        scanf("%s", st);
        mp1[string(st)]++;
    }

    for (i = 0; i < N; ++i) {
        scanf("%s", st);
        mp2[string(st)]++;
    }

    int ans = 0;
    for (auto iter : mp1) {
        ans = ans + min(iter.second, mp2[iter.first]);
    }

    printf("%d\n", ans);
    return 0;
}