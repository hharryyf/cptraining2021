#include <bits/stdc++.h>

using namespace std;

set<int> vis;

int f(int x) {
    string s = to_string(x);
    int ret = 0;
    for (auto v : s) {
        ret += (v - '0') * (v - '0');
    }
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n != 1) {
        if (vis.find(n) != vis.end()) {
            printf("UNHAPPY\n");
            return 0;
        }
        vis.insert(n);
        n = f(n);
    }

    printf("HAPPY\n");
    return 0;
}