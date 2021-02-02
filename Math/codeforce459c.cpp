#include <bits/stdc++.h>
using namespace std;

int n, d, k;
vector<int> vc;
vector<int> ans[1011];

int main() {
    int i;
    scanf("%d%d%d", &n, &k, &d);
    int curr = 1, good = 0;
    for (i = 0; i < d; ++i) {
        curr = curr * k;
        if (curr >= n) {
            good = 1;
            break;
        }
    }    

    if (!good) {
        printf("-1\n");
        return 0;
    }

    for (i = 0 ; i < n; ++i) {
        int j = i, bt = d - 1;
        ans[i] = vector<int>(d, 0);
        while (j > 0) {
            ans[i][bt--] = j % k;
            j /= k;
        }
    }

    for (i = 0 ; i < d; ++i) {
        for (int j = 0 ; j < n; ++j) {
            printf("%d ", ans[j][i] + 1);
        }
        printf("\n");
    }
    return 0;
}