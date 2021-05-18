#include <bits/stdc++.h>
using namespace std;

pair<int, int> search(int n, int k) {
    if (n == 2) {
        if (k == 0) {
            return {1, 1};            
        }
        if (k == 1) {
            return {1, 2};
        }
        if (k == 2) {
            return {2, 2};
        }
        if (k == 3) {
            return {2, 1};
        }
        return {-1, -1};
    }

    auto ret = search(n / 2, k % (n * n / 4));
    int coord = k / (n * n / 4);
    if (coord == 0) {
        swap(ret.first, ret.second);
        return ret;
    } else if (coord == 1) {
        ret.second += n / 2;
        return ret;
    } else if (coord == 2) {
        ret.first += n / 2;
        ret.second += n / 2;
        return ret;
    } else {
        auto rett = ret;
        rett.first = n + 1 - ret.second;
        rett.second = n / 2 + 1 - ret.first;
        return rett;
    }
}

int main() {
    int N, K;
    scanf("%d%d", &N, &K);
    K--;
    auto p = search(N, K);
    printf("%d %d\n", p.first, p.second);
    return 0;
}