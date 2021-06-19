#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

char s1[66], s2[66];
int N;

ll calc(char s[]) {
    ll ans = 0;
    if (s[N] == '1') ans = 2;
    else ans = 1;
    for (int i = N - 1; i >= 1; --i) {
        int od = N - i + 1;
        if (s[i] == '1') {
            ans = (1ll << od) - ans + 1;
        }
    }
    return ans;    
}

int main() {
    scanf("%d%s%s", &N, s1 + 1, s2 + 1);
    printf("%lld\n", llabs(calc(s2) - calc(s1)) - 1);    
    return 0;
}