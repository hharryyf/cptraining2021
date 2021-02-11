#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

int a[MAX_SIZE], N;
int zero, one;

int main() {
    int i, ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 1; i <= N; ++i) {
        if (a[i] == zero) {
            ans += (one != a[i]);
            one = a[i]; 
        } else if (a[i] == one) {
            ans += (zero != a[i]);
            zero = a[i];
        } else if (one == zero) {
            zero = a[i];
            ans++;
        } else {
            one = a[i];
            zero = 0;
            ans++;
        }
    }    
    printf("%d\n", ans);
    return 0;
}