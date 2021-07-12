#include <bits/stdc++.h>
typedef long double ld;
using namespace std;
pair<ld, int> ans[22];
ld w[3], S;
int main() {
    int i, j, k, N;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%Lf%Lf%Lf%Lf", &S, &w[0], &w[1], &w[2]);
        for (j = 0; j < 3; ++j) {
            for (k = j + 1; k < 3; ++k) {
                ans[i].first += (S * 2 - w[j] - w[k]) * w[j] * w[k];
            }
        }

        ans[i].first /= (S * S * S);
        ans[i].second = i;
    }

    sort(ans + 1, ans + 1 + N);
    for (i = 1; i <= N; ++i) {
        printf("%d ", ans[i].second);
    }
    printf("\n");
    return 0;
}