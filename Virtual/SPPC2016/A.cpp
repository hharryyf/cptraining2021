#include <bits/stdc++.h>

using namespace std;

pair<int, int> getindex(int val) {
    int x = 16001, y = 16001;
    int i = 1;
    while (i * i < val) {
        i += 2;
        x++;
        y--;
    }

    int curr = i * i, len = i;
    // cout << curr << endl;
    i = len;
    while (curr > val && i > 1) {
        curr--;
        x--;
        i--;
    }
    
    i = len;
    while (curr > val && i > 1) {
        curr--;
        y++;
        i--;
    }

    i = len;

    while (curr > val && i > 1) {
        curr--;
        i--;
        x++;
    }

    i = len;
    
    while (curr > val && i > 1) {
        curr--;
        i--;
        y--;
    }

    return make_pair(x, y);
}

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    pair<int, int> p1 = getindex(a), p2 = getindex(b);
    // cout << p1.first << " " << p1.second << endl;
    // cout << p2.first << " " << p2.second << endl;
    printf("%d\n", abs(p1.first - p2.first) + abs(p1.second - p2.second));
    return 0;
}