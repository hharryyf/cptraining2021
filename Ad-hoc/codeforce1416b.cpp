#include <bits/stdc++.h>
#define MAX_SIZE 10011
typedef long long ll;
using namespace std;
struct oper {
    int i, j;
    ll x;
    oper(int i=0, int j=0, ll x=0) : i(i), j(j), x(x) {}
};

ll a[MAX_SIZE];
int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, i;
        ll sm = 0;
        scanf("%d", &N);
        for (i = 1; i <= N; ++i) {
            scanf("%I64d", &a[i]);
            sm += a[i];
        }

        if (sm % N != 0) {
            printf("-1\n");
            continue;
        }
        sm /= N;
        vector<oper> op;
        for (i = 2; i <= N; ++i) {
            if (a[i] % i == 0) {
                op.push_back(oper(i, 1, a[i] / i));
            } else {
                op.push_back(oper(1, i, i - (a[i] % i)));
                op.push_back(oper(i, 1, a[i] / i + 1));
            }
        }

        for (i = 2; i <= N; ++i) {
            op.push_back(oper(1, i, sm));
        }
        printf("%d\n", (int) op.size());
        for (auto p : op) {
            printf("%d %d %I64d\n", p.i, p.j, p.x);
        }
    }
    return 0;
}