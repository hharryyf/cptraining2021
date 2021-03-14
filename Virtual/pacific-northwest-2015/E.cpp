#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int a[MAX_SIZE];
int N;

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    sort(a + 1, a + 1 + N);
    int ans = a[1] + a[N];
    for (i = 1; i <= N / 2; ++i) {
        ans = min(ans, a[i] + a[N - i + 1]);
    }

    cout << ans << endl;
    return 0;
}