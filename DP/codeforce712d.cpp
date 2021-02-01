#include <bits/stdc++.h>
#define MAX_SIZE 400411
using namespace std;
const int mod = 1000000007;
const int shift = 200211;

int add(int u, int v) {
    if (u > mod) u -= mod;
    if (v > mod) v -= mod;
    int ret = u + v;
    if (ret > mod) ret -= mod;
    return ret;
}

int idx(int x) {
    return x + shift;
}

int dp[2][MAX_SIZE];
int a, b, k, t;

int main() {
    int i, j;
    scanf("%d%d%d%d", &a, &b, &k, &t);
    int low = a - b - 2 * k * t, high = a - b + 2 * k * t; 
    dp[0][idx(a-b)] = 1;
    for (i = 1; i <= t; ++i) {
        for (j = low; j <= high; ++j) {
            
        }
    }
    return 0;
}